//
//  InputLayer.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__InputLayer__
#define __XP__InputLayer__

#include "cocos2d.h"
using namespace cocos2d;

class InputLayer : public Ref
{
public:
    InputLayer();
	~InputLayer();

	static InputLayer *create();
	void init();
private:
    void onTouchesBegan(const std::vector<Touch*>& touchs, Event* event);
    void onTouchesMoved(const std::vector<Touch*>& touchs, Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touchs, Event* event);
    void onTouchesCancelled(const std::vector<Touch*>& touchs, Event* event);
};

#endif /* defined(__XP__InputLayer__) */
