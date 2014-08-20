//
//  WorldLayer.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__WorldLayer__
#define __XP__WorldLayer__

#include "cocos2d.h"
using namespace cocos2d;

#include "InputProtocol.h"

class WorldLayer : public Node, public InputProtocol
{
public:
    WorldLayer();
	~WorldLayer();
    
	static WorldLayer *create();
	virtual bool init();
    
    void up();
    void down();
    void left();
    void right();
    void none();
    void buttons(int index, ButtonStatus buttonStatus);
    
    void checkInput(float delta);
    
    Scene *getWorld(){ return _world; }
private:
    Scene   *_world;
    Sprite  *_player;
    
    bool _isDebug;
    int _continueInput;
};

#endif /* defined(__XP__GameLayer__) */
