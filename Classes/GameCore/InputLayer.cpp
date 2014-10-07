#include "InputLayer.h"

InputLayer::InputLayer():
_touchListener(nullptr),
_multiTouchListener(nullptr),
_currButton(nullptr),
_target(nullptr)
{

}

InputLayer::~InputLayer()
{
    CCLOG("~InputLayer");
    auto *eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    eventDispatcher->removeEventListener(_touchListener);
    _touchListener = nullptr;
    
    eventDispatcher->removeEventListener(_multiTouchListener);
    _multiTouchListener = nullptr;
}

InputLayer *InputLayer::create()
{
	auto ref = new InputLayer();
    if (ref->init())
    {
        ref->autorelease();
        return ref;
    }
    else
    {
        CC_SAFE_DELETE(ref);
        return nullptr;
    }
}

bool InputLayer::init()
{
	auto *eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(false);
    _touchListener->onTouchBegan = CC_CALLBACK_2(InputLayer::onTouchBegan, this);
	_touchListener->onTouchMoved = CC_CALLBACK_2(InputLayer::onTouchMoved, this);
	_touchListener->onTouchEnded = CC_CALLBACK_2(InputLayer::onTouchEnded, this);
	_touchListener->onTouchCancelled = CC_CALLBACK_2(InputLayer::onTouchCancelled, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    
//    _multiTouchListener = EventListenerTouchAllAtOnce::create();
//	_multiTouchListener->onTouchesBegan = CC_CALLBACK_2(InputLayer::onTouchesBegan, this);
//	_multiTouchListener->onTouchesMoved = CC_CALLBACK_2(InputLayer::onTouchesMoved, this);
//	_multiTouchListener->onTouchesEnded = CC_CALLBACK_2(InputLayer::onTouchesEnded, this);
//	_multiTouchListener->onTouchesCancelled = CC_CALLBACK_2(InputLayer::onTouchesCancelled, this);
//    eventDispatcher->addEventListenerWithSceneGraphPriority(_multiTouchListener, this);
    
    _pnlStick = Node::create();
    _imgStickBg = Sprite::create("stickBg.png");
    _imgStickBg->setScale(0.5);
    _pnlStick->addChild(_imgStickBg);
    _imgStick = Sprite::create("stick.png");
    _imgStick->setScale(0.5);
    _pnlStick->addChild(_imgStick);
    _pnlStick->setPosition(Vec2(50, 50));
    addChild(_pnlStick);
    
    auto btnA = Sprite::create("a.png");
    auto btnB = Sprite::create("b.png");
    auto btnC = Sprite::create("c.png");
    auto btnD = Sprite::create("d.png");
    btnA->setPosition(Vec2(400, 100));
    btnB->setPosition(Vec2(450, 100));
    btnC->setPosition(Vec2(400, 50));
    btnD->setPosition(Vec2(450, 50));
    btnA->setScale(0.5);
    btnB->setScale(0.5);
    btnC->setScale(0.5);
    btnD->setScale(0.5);
    _btnButtons.pushBack(btnA);
    _btnButtons.pushBack(btnB);
    _btnButtons.pushBack(btnC);
    _btnButtons.pushBack(btnD);
    auto iter = _btnButtons.begin();
    for (int i = 0; iter != _btnButtons.end(); iter++)
    {
        auto button = *iter;
        button->setTag(i++);
        CCLOG("add button, tag : %d", button->getTag());
        addChild(button);
    }
    
    _prevPos = Vec2::ZERO;
    _orginScale = (_btnButtons.back())->getScaleX();
    
    return true;
}

void InputLayer::dispatch(Vec2 &pos, InputType inputType)
{
    if (pos.x <= 240)
    {
        stickHandle(pos, inputType);
        buttonsHandle(pos, INPUT_CANCELLED);
    }
    else
    {
        stickHandle(pos, INPUT_CANCELLED);
        buttonsHandle(pos, inputType);
    }
}

void InputLayer::stickHandle(Vec2 &pos, InputType inputType)
{
    auto localPos = convertToNodeSpace(pos);
    switch (inputType)
    {
        case INPUT_BEGAN:
        {
            _prevPos = localPos;
            
            _imgStickBg->runAction(FadeIn::create(0.3));
            _imgStick->runAction(FadeIn::create(0.3));
            _pnlStick->setPosition(localPos);
            break;
        }
        case INPUT_MOVED:
        {
            auto moveVector = localPos - _prevPos;
            auto moveAngle = moveVector.getAngle();
            auto moveDegree = MATH_RAD_TO_DEG(moveAngle);
            auto moveLength = moveVector.getLength();
            
            //CCLOG("moveDegree : %f     moveLength : %f", moveDegree, moveLength);
            if (moveLength > STICK_MAX_R)
            {
                auto rate = STICK_MAX_R / moveLength;
                moveVector = moveVector * rate;
            }
            
            auto oldPos = _imgStick->getPosition();
            _imgStick->setPosition(moveVector);
            
            if (_target)
            {
                if (moveDegree >= -45 && moveDegree < 45)
                {
                    _target->right();
                }
                else if (moveDegree >= 45 && moveDegree < 135)
                {
                    _target->up();
                }
                else if (moveDegree >= -135 && moveDegree < -45)
                {
                    _target->down();
                }
                else
                {
                    _target->left();
                }
            }
            
            break;
        }
        case INPUT_ENDED:
        {
            _imgStickBg->runAction(FadeOut::create(0.3));
            _imgStick->runAction(FadeOut::create(0.3));
            _imgStick->setPosition(Vec2::ZERO);
            
            if (_target)
            {
                _target->none();
            }
            break;
        }
        case INPUT_CANCELLED:
        {
            /*
            _imgStickBg->runAction(FadeOut::create(0.3));
            _imgStick->runAction(FadeOut::create(0.3));
            _imgStick->setPosition(Vec2::ZERO);
            
            if (_target)
            {
                _target->none();
            }
             */
            break;
        }
        default:
            break;
    }
}

void InputLayer::buttonsHandle(Vec2 &pos, InputType inputType)
{
    if (inputType == INPUT_BEGAN)
    {
        auto iter = _btnButtons.begin();
        for ( ; iter != _btnButtons.end(); iter++)
        {
            auto button = *iter;
            auto localPos = button->convertToNodeSpace(pos);
            auto rect = Rect( button->getPositionX() - button->getContentSize().width * button->getAnchorPoint().x,
                             button->getPositionY() - button->getContentSize().height * button->getAnchorPoint().y,
                             button->getContentSize().width, button->getContentSize().height);
            rect.origin = Vec2::ZERO;
            
            if (rect.containsPoint(localPos))
            {
                _currButton = button;
            }
        }
    }
    
    if (_currButton)
    {
        auto index = _currButton->getTag();
        CCLOG("_currButton tag : %d", index);
        
        switch (inputType)
        {
            case INPUT_BEGAN:
            {
                _currButton->runAction(ScaleTo::create(0.1, _orginScale + 0.2));
                if (_target)
                {
                    _target->buttons(index, InputProtocol::ButtonPress);
                }
                break;
            }
            case INPUT_MOVED:
            {
                
                break;
            }
            case INPUT_ENDED:
            {
                _currButton->runAction(ScaleTo::create(0.1, _orginScale));
                if (_target)
                {
                    _target->buttons(index, InputProtocol::ButtonRelease);
                }
                break;
            }
            case INPUT_CANCELLED:
            {
                _currButton->runAction(ScaleTo::create(0.1, _orginScale));
                break;
            }
            default:
                break;
        }
    }
}

bool InputLayer::onTouchBegan(Touch *touch, Event* event)
{
    auto pos = touch->getLocation();
    //CCLOG("Began (%d, %d)", (int)pos.x, (int)pos.y);
    dispatch(pos, INPUT_BEGAN);
    return true;
}
void InputLayer::onTouchMoved(Touch *touch, Event* event)
{
    auto pos = touch->getLocation();
    //CCLOG("Moved (%d, %d)", (int)pos.x, (int)pos.y);
    dispatch(pos, INPUT_MOVED);
}
void InputLayer::onTouchEnded(Touch *touch, Event* event)
{
    auto pos = touch->getLocation();
    //CCLOG("Ended (%d, %d)", (int)pos.x, (int)pos.y);
    dispatch(pos, INPUT_ENDED);

}
void InputLayer::onTouchCancelled(Touch *touch, Event* event)
{
    auto pos = touch->getLocation();
    //CCLOG("Cancelled (%d, %d)", (int)pos.x, (int)pos.y);
    dispatch(pos, INPUT_CANCELLED);
}

void InputLayer::onTouchesBegan(const std::vector<Touch*>& touchs, Event* event)
{
	std::vector<Touch *>::const_iterator iter = touchs.begin();
	for ( ; iter != touchs.end(); iter++)
	{
		auto pos = (*iter)->getLocation();
		CCLOG("onTouchesBegan (%d, %d)", (int)pos.x, (int)pos.y);
	}
}

void InputLayer::onTouchesMoved(const std::vector<Touch*>& touchs, Event* event)
{
    std::vector<Touch *>::const_iterator iter = touchs.begin();
	for ( ; iter != touchs.end(); iter++)
	{
		auto pos = (*iter)->getLocation();
		CCLOG("onTouchesMoved (%d, %d)", (int)pos.x, (int)pos.y);
	}
}

void InputLayer::onTouchesEnded(const std::vector<Touch*>& touchs, Event* event)
{
    std::vector<Touch *>::const_iterator iter = touchs.begin();
	for ( ; iter != touchs.end(); iter++)
	{
		auto pos = (*iter)->getLocation();
		CCLOG("onTouchesEnded (%d, %d)", (int)pos.x, (int)pos.y);
	}
}

void InputLayer::onTouchesCancelled(const std::vector<Touch*>& touchs, Event* event)
{
    std::vector<Touch *>::const_iterator iter = touchs.begin();
	for ( ; iter != touchs.end(); iter++)
	{
		auto pos = (*iter)->getLocation();
		CCLOG("onTouchesCancelled (%d, %d)", (int)pos.x, (int)pos.y);
	}
}