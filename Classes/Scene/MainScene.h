//
//  MainScene.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__MainScene__
#define __XP__MainScene__

#include "Framework.h"
#include "SceneDefine.h"

class MainScene : public Controller
{
public:
    DECLARE_CLASS_CREATE(MainScene)
    
    MainScene();
	~MainScene();
    
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
    Button *_btnGo;
	Button *_btnRead;
};

#endif /* defined(__XP__MainScene__) */
