#include "WorldLayer.h"

WorldLayer::WorldLayer():
_isDebug(false),
_continueInput(0)
{

}

WorldLayer::~WorldLayer()
{
    CCLOG("~WorldLayer");
}

WorldLayer *WorldLayer::create()
{
	WorldLayer *ref = new WorldLayer();
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

bool WorldLayer::init()
{
	bool isSuccess = false;
	if (Node::init())
	{
		_world = Scene::createWithPhysics();
        _world->getPhysicsWorld()->setGravity(Vec2(0.0f, -980.0f * 0.5));
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        CCLOG("visibleSize : %f, %f", visibleSize.width, visibleSize.height);
        
        auto ndFrame = Node::create();
        auto material = PhysicsMaterial(0.1f, 0.5f, 0.0f);
        auto bdFrame = PhysicsBody::createEdgeBox(visibleSize, material);
        bdFrame->getShape(0)->setFriction(2.0);
        ndFrame->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
        ndFrame->setPhysicsBody(bdFrame);
        _world->addChild(ndFrame);
        
        _player = Sprite::create("a.png");
        auto bdPlayer = PhysicsBody::createBox(Size(_player->getContentSize()));
        //auto bdPlayer = PhysicsBody::createCircle(_player->getContentSize().width/2.0);
        bdPlayer->setVelocityLimit(200);
        bdPlayer->getFirstShape()->setRestitution(0.0);
        bdPlayer->setRotationEnable(false);
        _player->setPhysicsBody(bdPlayer);
        _player->setPosition(Vec2(240, 160));
        _world->addChild(_player);
        
        addChild(_world);
        
        auto sche = Director::getInstance()->getScheduler();
        sche->schedule(schedule_selector(WorldLayer::checkInput), this, 0, false);
        
		isSuccess = true;
	}
	
	return isSuccess;
}

void WorldLayer::checkInput(float delta)
{
    auto bdPlayer = _player->getPhysicsBody();
    auto velocity = bdPlayer->getVelocity();
    auto absVolicity = fabsf(velocity.x);
    
    bdPlayer->resetForces();
    
    //CCLOG("_continueInput : %d", _continueInput);
    if (_continueInput == 0)
    {
        
    }
    else if (_continueInput == 1)
    {
        
    }
    else if (_continueInput == 2)
    {
        
    }
    else if (_continueInput == 3)
    {
        bdPlayer->applyForce(Vec2(-1000000, 0));
    }
    else if (_continueInput == 4)
    {
        bdPlayer->applyForce(Vec2(1000000, 0));
    }
}

void WorldLayer::up()
{
    CCLOG("up");
    _continueInput = 1;
}
void WorldLayer::down()
{
    CCLOG("down");
    _continueInput = 2;
}

void WorldLayer::left()
{
    CCLOG("left");
    _continueInput = 3;
}

void WorldLayer::right()
{
    CCLOG("right");
    _continueInput = 4;
}

void WorldLayer::none()
{
    CCLOG("none");
    _continueInput = 0;
}

void WorldLayer::buttons(int index, ButtonStatus buttonStatus)
{
    if (buttonStatus == InputProtocol::ButtonPress)
    {
        CCLOG("buttons press : %d", index);
    }
    else if (buttonStatus == InputProtocol::ButtonRelease)
    {
        CCLOG("buttons release : %d", index);
        if (index == 3)
        {
            if (!_isDebug)
            {
                _world->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
                _isDebug = true;
            }
            else
            {
                _world->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
                _isDebug = false;
            }
        }
        else if (index == 1)
        {
            CCLOG("Jump !");
            _player->getPhysicsBody()->applyImpulse(Vec2(0, 200000));
        }
    }
}