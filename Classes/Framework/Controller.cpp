#include "Controller.h"

Controller::Controller()
{
    _name = "Controller";
	_scene = Scene::create();
	_scene->retain();
	_data = NULL;
    _gameLayer = NULL;
}

Controller::~Controller()
{
	CC_SAFE_RELEASE(_scene);
	CC_SAFE_RELEASE(_data);
}


void Controller::dispatchEvent(std::string event, Ref *data)
{
    
}

Widget *Controller::loadScene(std::string jsonFileName)
{
	auto scene = GUIReader::getInstance()->widgetFromJsonFile(jsonFileName.c_str());
	
	Scene *gameLayer = (Scene *)scene->getChildren().at(0);
	_gameLayer = gameLayer;
    
    sceneAdpat(scene);
	_scene->addChild(scene);
    
	return scene;
}

void Controller::sceneAdpat(Node *scene)
{
    if (!scene) return;
		
    Scene *gameLayer = (Scene *)scene->getChildren().at(0);
    
    auto glView = Director::getInstance()->getOpenGLView();
    
    auto scaleX = glView->getScaleX();
    auto scaleY = glView->getScaleY();
    auto x1 = glView->getFrameSize().width/(scaleY);
    auto y1 = glView->getFrameSize().height/(scaleX);
    
    if (scaleX > scaleY)
    {
        CCLOG("ipad layout");
        scene->setScaleX(scaleY/scaleX);
        auto fillBarLeft  = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Fill.png"));
		auto fillBarRight = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("Fill.png"));
		auto tempX = fillBarRight->getContentSize().width/2;
        
        fillBarRight->setPosition(Vec2(320+tempX-15,240));
        fillBarLeft->setPosition(Vec2(-tempX+15,240));
        fillBarLeft->setFlippedX(true);
        
		auto tempScaleX = 22/fillBarRight->getContentSize().width;
		auto tempScaleY = 480/fillBarRight->getContentSize().height;
        fillBarRight->setScaleX(tempScaleX);
        fillBarRight->setScaleY(tempScaleY);
        fillBarLeft->setScaleX(tempScaleX);
        fillBarLeft->setScaleY(tempScaleY);
        
        scene->addChild(fillBarLeft,64,64);
        scene->addChild(fillBarRight,64,63);
    }
    else if (scaleX < scaleY)
    {
        CCLOG("iphone 5 layout");
        gameLayer->setScaleY(scaleX/scaleY);
		Layer *UpLayer = (Layer *)gameLayer->getChildByTag(1);
        Layer *DownLayer = (Layer *)gameLayer->getChildByTag(3);
        if (UpLayer)
        {
            if (y1 >= 480)
            {
                auto orignY = UpLayer->getPositionY();
                UpLayer->setPositionY(orignY+(y1 - 480)/2);
                auto PostionY = UpLayer->getPositionY();
            }
        }
        if (DownLayer)
        {
            if (y1 >= 480)
            {
                DownLayer->setPositionY((480-y1)/2);
            }
        }
    }
    else
    {
        CCLOG("iphone classic layout");
    }
}


Ref *Controller::getData()
{
    return _data;
}

void Controller::setData(Ref *data)
{
    CC_SAFE_RETAIN(data);
    CC_SAFE_RELEASE(_data);
    _data = data;
}