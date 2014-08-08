//
//  MainScene.cpp
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#include "GameScene.h"

IMP_CLASS_CREATE(GameScene)

GameScene::GameScene()
{
    CCLOG("GameScene");
}

GameScene::~GameScene()
{
    CCLOG("~GameScene");
}

void GameScene::init(Ref *data)
{
    _name = GAME_SCENE;
    auto scene = loadScene("XPUI_GameScene.json");
    
    _btnBack   = (Button *)scene->getChildByName("Panel_1")->getChildByName("btnBack");
    
	_btnBack->addTouchEventListener(this, SEL_TouchEvent(&GameScene::buttonEvent));

    auto panel3 = (Button *)scene->getChildByName("Panel_3");
	_gameLayer = GameLayer::create();
	panel3->addChild(_gameLayer);
    
    
    // debug
    CCLOG("============ GameScene::init 1");
    printChildren(scene);
    CCLOG("============ GameScene::init 2");
    
    CCLOG("top scene isEnabled, %d", scene->isEnabled());
    CCLOG("top scene isTouchEnabled, %d", scene->isTouchEnabled());
    
    auto layout = (Layout *)scene->getChildByName("Panel_1");
    CCLOG("layout isEnabled, %d", layout->isEnabled());
    CCLOG("layout isTouchEnabled, %d", layout->isTouchEnabled());
}

std::vector<std::string> *GameScene::expectedEvents()
{
    return NULL;
}

void GameScene::handleEvent(std::string event, Ref *data)
{
    
}

void GameScene::dispatchEvent(std::string event, Ref *data)
{
    
}

void GameScene::reset()
{
    
}

void GameScene::refresh()
{
    
}

void GameScene::buttonEvent(Ref *target, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            
            break;
        case Widget::TouchEventType::MOVED:
            
            break;
        case Widget::TouchEventType::ENDED:
			if (target == _btnBack)
            {
                SceneManager::getInstance()->pop();
            }
            break;
        case Widget::TouchEventType::CANCELED:
            
            break;
        default:
            break;
    }
}