#include "SceneManager.h"
#include "Controller.h"
#include "ControllerFactory.h"
#include "EventManager.h"

static SceneManager *s_pSceneManager = NULL;

SceneManager::SceneManager()
{
	
}

SceneManager *SceneManager::getInstance()
{
	if (!s_pSceneManager)
	{
		s_pSceneManager = new SceneManager();
		s_pSceneManager->init();
	}

	return s_pSceneManager;
}

bool SceneManager::init()
{
	_rootScene = Scene::create();
	_rootScene->setAnchorPoint(Vec2::ZERO);
	_rootScene->setPosition(Vec2::ZERO);
	_rootScene->retain();
    _size = 0;

	return true;
}

SceneManager::~SceneManager()
{
	CC_SAFE_RELEASE(_rootScene);

	s_pSceneManager = NULL;
}

void SceneManager::push(std::string name, Ref *data)
{
    auto obj = ControllerFactory::getInstance()->getController(name, data);
	
    if (!obj)
    {
        CCLOG("ERROR ! Can't create instance : '%s' .", name.c_str());
    }
    
    if (obj->isRemoveBefore() && _size > 0)
    {
        CCLOG("Release controller : %d", _size);
        removeScene(_size);
    }
            
    _size = _size + 1;
    _nameStack.push_back(name);
    _cntrStack.pushBack(obj);
    if (data)
        _dataStack.pushBack(data);
    else
        _dataStack.pushBack(NULL_);
    
    auto events = obj->expectedEvents();
    if (events)
    {
        std::vector<std::string>::iterator it;
        for (it=events->begin(); it!=events->end(); it++)
        {
            auto event = *(it);
            EventManager::getInstance()->addListener(event, obj);
        }
    }
    
    _rootScene->addChild(obj->getScene(), _size, _size);
    
	// should print before reset and refresh, it maybe push another scene in refresh function.
    printStack();
	
    obj->reset();
	
    obj->refresh();
}

void SceneManager::pop()
{
    if (_size <= 0)
    {
		CCLOG("Scene stack is empty !");
		return;
    }
    
    removeScene(_size, true);
    
    resumeScene(_size);
    
    printStack();
}

void SceneManager::popToScene(std::string name)
{
    int index = -1;
    for (int i=_size-1; i>=0; i--)
    {
        if (_nameStack.at(i) == name)
        {
            index = i;
            break;
        }
    }
	
    if (index == -1 )
    {
        CCLOG("No scene named: %s", name.c_str());
        return;
    }
                
    CCLOG("Pop to scene name: %s index: %d", name.c_str(), index);
    
    for (int i=_size-1; i>=index+1; i--)
    {
        removeScene(_size, true);
    }
                    
    resumeScene(_size);
    
    printStack();
}

void SceneManager::replace(std::string name, Ref *data)
{
    pop();
    push(name, data);
}

void SceneManager::removeScene(int index, bool isPop)
{
    if (index < 1 || index > _size)
    {
        CCLOG("Can not remove scene index: %d", index);
		return;
    }
    
    if (_cntrStack.at(_size - 1))
    {
        _rootScene->removeChildByTag(_size, true);
        EventManager::getInstance()->removeListener(_cntrStack.at(_size - 1));
		//_cntrStack.at(_size)->destroy();
    }
            
    // if remove top scene, pop it
    if (isPop == true )
    {
        _nameStack.pop_back();
		_cntrStack.popBack();
		_dataStack.popBack();
		_size = _size - 1;
    }
    else
    {
        _cntrStack.replace(_size - 1, (Controller *)NULL_);
    }
}

void SceneManager::removeScene(int index)
{
    removeScene(index, false);
}

void SceneManager::resumeScene(int index)
{
    if (index < 1 || index > _size)
    {
        CCLOG("Can not resume scene index: %d", index);
		return;
    }
    
    if (_cntrStack.at(index - 1) == (Controller *)NULL_)
    {
        auto name = _nameStack.at(index - 1);
		auto data = _dataStack.at(index - 1);
        
        if (data == NULL_) data = NULL;
        
        auto obj = ControllerFactory::getInstance()->getController(name, data);
        if (!obj)
        {
            CCLOG("ERROR ! Can't create instance : '%s' .", name.c_str());
			return;
        }
        
        _cntrStack.replace(index - 1, obj);
        
        auto events = obj->expectedEvents();
        if (events)
        {
            std::vector<std::string>::iterator it;
            for (it=events->begin(); it!=events->end(); it++)
            {
                auto event = *(it);
                EventManager::getInstance()->addListener(event, obj);
            }
        }
        
        _rootScene->addChild(obj->getScene(), _size, _size);
        
        obj->reset();
        
        obj->refresh();
    }
}

void SceneManager::refreshTopScene()
{
    if (_size > 0 )
		return;
        
    _cntrStack.at(_size - 1)->reset();
    _cntrStack.at(_size - 1)->refresh();
}

Controller *SceneManager::getTopScene()
{
    return _cntrStack.at(_size - 1);
}


void SceneManager::printStack()
{
    CCLOG("==========================================================================");
	CCLOG("== size : %d", _size);
    for (int i=_size - 1; i >= 0; i--)
    {
        auto name = _nameStack.at(i).c_str();
        auto controller = _cntrStack.at(i);
        auto data = _dataStack.at(i);
        if (controller == (Controller *)NULL_ && data != NULL_)
            CCLOG("%d\t[Name: %s]\t\t[Controller: NULL]\t\t[Data: 0x%08x]", i + 1, name, (void*)data);
        else if (controller != (Controller *)NULL_ && data == NULL_)
            CCLOG("%d\t[Name: %s]\t\t[Controller: 0x%08x]\t\t[Data: NULL]", i + 1, name, (void*)controller);
        else if (controller == (Controller *)NULL_ && data == NULL_)
            CCLOG("%d\t[Name: %s]\t\t[Controller: NULL]\t\t[Data: NULL]", i + 1, name);
        else
            CCLOG("%d\t[Name: %s]\t\t[Controller: 0x%08x]\t\t[Data: 0x%08x]", i + 1, name, (void*)controller, (void*)data);
    }
    printChildren(_rootScene);
    CCLOG("==========================================================================");
}

void printChildren(Node *node)
{
    auto children = node->getChildren();
    auto iter = children.begin();
    
    for (; iter != children.end(); iter++)
    {
        auto child = (*iter);
        CCLOG("printChildren %s", child->getDescription().c_str());
    }
    
}