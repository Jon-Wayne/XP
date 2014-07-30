//
//  MainScene.cpp
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#include "MainScene.h"

IMP_CLASS_CREATE(MainScene)

MainScene::MainScene()
{
    CCLOG("MainScene");
}

MainScene::~MainScene()
{
    CCLOG("~MainScene");
	
}

void MainScene::init(Ref *data)
{
    _name = MAIN_SCENE;
    auto scene = loadScene("XPUI_MainScene.json");
    
    _btnGo = (Button *)scene->getChildByName("Panel_2")->getChildByName("btnGo");
	_btnRead = (Button *)scene->getChildByName("Panel_2")->getChildByName("Button_19");
    
	//_btnGo->addTouchEventListener(CC_CALLBACK_2(MainScene::buttonEvent, this));
	_btnGo->addTouchEventListener(this, SEL_TouchEvent(&MainScene::buttonEvent));
}

std::vector<std::string> *MainScene::expectedEvents()
{
    return NULL;
}

void MainScene::handleEvent(std::string event, Ref *data)
{
    
}

void MainScene::dispatchEvent(std::string event, Ref *data)
{
    
}

void MainScene::reset()
{
    
}

void MainScene::refresh()
{
    
}

void MainScene::buttonEvent(Ref *target, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            
            break;
        case Widget::TouchEventType::MOVED:
            
            break;
        case Widget::TouchEventType::ENDED:
            if (target == _btnGo)
            {
				/*auto sched = Director::getInstance()->getScheduler();
				sched->scheduleSelector(*/
				
				//_btnGo->removeFromParentAndCleanup(true);
				//_btnGo->addTouchEventListener(nullptr, nullptr);
                SceneManager::getInstance()->push(GAME_SCENE, NULL);
            }
            break;
        case Widget::TouchEventType::CANCELED:
            
            break;
        default:
            break;
    }
}