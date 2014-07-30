//
//  SceneInit.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__SceneInit__
#define __XP__SceneInit__


#include "Framework.h"
#include "SceneDefine.h"

#include "MainScene.h"
#include "GameScene.h"

void SceneInit()
{
    ControllerFactory::getInstance()->registerFactoryCreate(MAIN_SCENE, MainScene::CreateMainScene);
    ControllerFactory::getInstance()->registerFactoryCreate(GAME_SCENE, GameScene::CreateGameScene);
    
    Director::getInstance()->runWithScene(SceneManager::getInstance()->getRootScene());
    
    SceneManager::getInstance()->push(MAIN_SCENE, NULL);
}


#endif /* defined(__XP__SceneInit__) */
