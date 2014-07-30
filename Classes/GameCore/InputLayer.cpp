#include "InputLayer.h"

InputLayer::InputLayer()
{

}

InputLayer::~InputLayer()
{

}

InputLayer *InputLayer::create()
{
	auto ref = new InputLayer();
	ref->init();
	ref->autorelease();

	return ref;
}

void InputLayer::init()
{
	auto *eventListener = EventListenerTouchAllAtOnce::create();
	eventListener->onTouchesBegan = CC_CALLBACK_2(InputLayer::onTouchesBegan, this);
	eventListener->onTouchesMoved = CC_CALLBACK_2(InputLayer::onTouchesMoved, this);
	eventListener->onTouchesEnded = CC_CALLBACK_2(InputLayer::onTouchesEnded, this);
	eventListener->onTouchesCancelled = CC_CALLBACK_2(InputLayer::onTouchesCancelled, this);

	auto *eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithFixedPriority(eventListener, -100);
}

void InputLayer::onTouchesBegan(const std::vector<Touch*>& touchs, Event* event)
{
	std::vector<Touch *>::const_iterator iter = touchs.begin();
	for ( ; iter != touchs.end(); iter++)
	{
		auto pos = (*iter)->getLocation();
		CCLOG("(%d, %d)", (int)pos.x, (int)pos.y);
	}
}

void InputLayer::onTouchesMoved(const std::vector<Touch*>& touchs, Event* event)
{

}

void InputLayer::onTouchesEnded(const std::vector<Touch*>& touchs, Event* event)
{

}

void InputLayer::onTouchesCancelled(const std::vector<Touch*>& touchs, Event* event)
{

}