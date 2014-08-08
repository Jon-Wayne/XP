#include "GameLayer.h"

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{
    CCLOG("~GameLayer");
}

GameLayer *GameLayer::create()
{
	GameLayer *ref = new GameLayer();
	if (ref->init())
	{
        ref->autorelease();
		return ref;
	}
	else
	{
		CC_SAFE_DELETE(ref);
		return NULL;
	}
}

bool GameLayer::init()
{
	bool isSuccess = false;
	if (Node::init())
	{
		_inputLayer = InputLayer::create();
        this->addChild(_inputLayer);
		isSuccess = true;
	}
	
	return isSuccess;
}