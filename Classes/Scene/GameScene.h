//
//  MainScene.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__GameScene__
#define __XP__GameScene__

#include "Framework.h"
#include "SceneDefine.h"
#include "../GameCore/GameLayer.h"

class GameScene : public Controller
{
public:
    DECLARE_CLASS_CREATE(GameScene)
    
    GameScene();
	~GameScene();
    
    void init(Ref *data);
	
	bool isRemoveBefore(){ return true; };
    
    std::vector<std::string> *expectedEvents();
    void handleEvent(std::string event, Ref *data);
    void dispatchEvent(std::string event, Ref *data);
    
    void reset();
    void refresh();
    
	void viewLoad(){};
	void viewAppear(){};
	void viewDisappear(){};
	void viewUnload(){};
private:
    void buttonEvent(Ref *target, Widget::TouchEventType type);
private:
    Button *_btnBack;

	GameLayer *_gameLayer;
};

#endif /* defined(__XP__GameScene__) */
