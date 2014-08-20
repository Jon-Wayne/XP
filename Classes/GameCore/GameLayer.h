//
//  GameLayer.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__GameLayer__
#define __XP__GameLayer__

#include "cocos2d.h"
using namespace cocos2d;

#include "InputLayer.h"
#include "WorldLayer.h"

class GameLayer : public Node
{
public:
    GameLayer();
	~GameLayer();

	static GameLayer *create();
	virtual bool init();
private:
    WorldLayer *_worldLayer;
    InputLayer *_inputLayer;
    
    
};

#endif /* defined(__XP__GameLayer__) */
