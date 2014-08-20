#include "GameLayer.h"

#include "RoleManager.h"

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
        _worldLayer = WorldLayer::create();
        this->addChild(_worldLayer);
        
		_inputLayer = InputLayer::create();
        _inputLayer->setTarget(_worldLayer);
        this->addChild(_inputLayer);
        
        auto rm = RoleManager::getInstance();
        rm->setTarget(_worldLayer->getWorld());
        
		isSuccess = true;
	}
	
	return isSuccess;
}