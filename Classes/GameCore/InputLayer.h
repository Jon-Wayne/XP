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

#include "InputProtocol.h"

#define STICK_MAX_R 20.0

class InputLayer : public Node
{
public:
    typedef enum _InputType
    {
        INPUT_BEGAN,
        INPUT_MOVED,
        INPUT_ENDED,
        INPUT_CANCELLED
    } InputType;
    
    InputLayer();
	~InputLayer();

	static InputLayer *create();
	bool init();
    
    void setTarget(InputProtocol *target){ _target = target; }
    InputProtocol * getTarget(){ return _target; }
private:
    void dispatch(Vec2 &pos, InputType inputType);
    void stickHandle(Vec2 &pos, InputType inputType);
    void buttonsHandle(Vec2 &pos, InputType inputType);
    
    bool onTouchBegan(Touch *touch, Event* event);
    void onTouchMoved(Touch *touch, Event* event);
    void onTouchEnded(Touch *touch, Event* event);
    void onTouchCancelled(Touch *touch, Event* event);
    
    void onTouchesBegan(const std::vector<Touch*>& touchs, Event* event);
    void onTouchesMoved(const std::vector<Touch*>& touchs, Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touchs, Event* event);
    void onTouchesCancelled(const std::vector<Touch*>& touchs, Event* event);
private:
    EventListenerTouchOneByOne *_touchListener;
    EventListenerTouchAllAtOnce *_multiTouchListener;
    
    Node   *_pnlStick;
    Sprite *_imgStickBg;
    Sprite *_imgStick;
    
    Vector<Sprite *> _btnButtons;
    
    Vec2 _prevPos;
    float _orginScale;
    Sprite *_currButton;
    
    InputProtocol *_target;
};

#endif /* defined(__XP__InputLayer__) */
