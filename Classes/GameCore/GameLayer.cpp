#include "GameLayer.h"

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{
	_inputLayer->release();
}

GameLayer *GameLayer::create()
{
	GameLayer *ref = new GameLayer();
	if (ref->init())
	{
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
		_inputLayer->retain();
		isSuccess = true;
	}
	
	return isSuccess;
}