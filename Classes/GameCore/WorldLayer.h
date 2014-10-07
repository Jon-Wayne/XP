//
//  WorldLayer.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__WorldLayer__
#define __XP__WorldLayer__

#define PLAYER_START_FORCE  1000000.0f
#define PLAYER_MOVE_FORCE   300000.0f

#include "cocos2d.h"
using namespace cocos2d;

#include "InputProtocol.h"
#include "RoleManager.h"

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
    void setControlRole(Role *controlRole);
private:
    Scene   *_world;    //  physical world and parent node of all body nodes
    
    Role    *_controlRole;
    Sprite  *_player;   //  player body node renference
    int     _playerMoveForceDir;
    Vec2    _playerForce;
    
    bool _isDebug;
    int _oldContinueInput;
    int _continueInput;
};

#endif /* defined(__XP__GameLayer__) */
