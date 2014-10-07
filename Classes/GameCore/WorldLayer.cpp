#include "WorldLayer.h"

WorldLayer::WorldLayer():
_world(nullptr),
_player(nullptr),
_playerForce(Vec2::ZERO),
_isDebug(false),
_oldContinueInput(0),
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
        
        addChild(_world);
        
        auto sche = Director::getInstance()->getScheduler();
        sche->schedule(schedule_selector(WorldLayer::checkInput), this, 0, false);
        
		isSuccess = true;
	}
	
	return isSuccess;
}

void WorldLayer::setControlRole(Role *controlRole)
{
    if (controlRole)
    {
        _controlRole = controlRole;
        _player = _controlRole->getSprite();
    }
    else
    {
        _controlRole = nullptr;
        _player = nullptr;
    }
}

void WorldLayer::checkInput(float delta)
{
    if (!_controlRole || !_player) return;
    
    auto bdPlayer = _player->getPhysicsBody();
    
    auto velocity = bdPlayer->getVelocity();
    auto absVolicity = fabsf(velocity.x);
    
    //bdPlayer->resetForces();
    
//    CCLOG("_oldContinueInput _continueInput %d, %d", _oldContinueInput, _continueInput);
    
    //CCLOG("_continueInput : %d", _continueInput);
    if (_continueInput == 0)
    {
        if (_playerForce.x == -PLAYER_START_FORCE)
        {
            bdPlayer->applyForce(Vec2(PLAYER_START_FORCE, 0.0f));
        }
        else if (_playerForce.x == -PLAYER_MOVE_FORCE)
        {
            bdPlayer->applyForce(Vec2(PLAYER_MOVE_FORCE, 0.0f));
        }
        else if (_playerForce.x == PLAYER_START_FORCE)
        {
            bdPlayer->applyForce(Vec2(-PLAYER_START_FORCE, 0.0f));
        }
        else if (_playerForce.x == PLAYER_MOVE_FORCE)
        {
            bdPlayer->applyForce(Vec2(-PLAYER_MOVE_FORCE, 0.0f));
        }
        _playerForce.x = 0.0f;
    }
    // Up
    else if (_continueInput == 1)
    {
        if (_playerForce.x == -PLAYER_START_FORCE)
        {
            bdPlayer->applyForce(Vec2(PLAYER_START_FORCE, 0.0f));
        }
        else if (_playerForce.x == -PLAYER_MOVE_FORCE)
        {
            bdPlayer->applyForce(Vec2(PLAYER_MOVE_FORCE, 0.0f));
        }
        else if (_playerForce.x == PLAYER_START_FORCE)
        {
            bdPlayer->applyForce(Vec2(-PLAYER_START_FORCE, 0.0f));
        }
        else if (_playerForce.x == PLAYER_MOVE_FORCE)
        {
            bdPlayer->applyForce(Vec2(-PLAYER_MOVE_FORCE, 0.0f));
        }
        _playerForce.x = 0.0f;
    }
    // Down
    else if (_continueInput == 2)
    {
        if (_playerForce.x == -PLAYER_START_FORCE)
        {
            bdPlayer->applyForce(Vec2(PLAYER_START_FORCE, 0.0f));
        }
        else if (_playerForce.x == -PLAYER_MOVE_FORCE)
        {
            bdPlayer->applyForce(Vec2(PLAYER_MOVE_FORCE, 0.0f));
        }
        else if (_playerForce.x == PLAYER_START_FORCE)
        {
            bdPlayer->applyForce(Vec2(-PLAYER_START_FORCE, 0.0f));
        }
        else if (_playerForce.x == PLAYER_MOVE_FORCE)
        {
            bdPlayer->applyForce(Vec2(-PLAYER_MOVE_FORCE, 0.0f));
        }
        _playerForce.x = 0.0f;
    }
    // Left
    else if (_continueInput == 3)
    {
        if (_playerForce.x == 0.0f)
        {
            bdPlayer->applyForce(Vec2(-PLAYER_START_FORCE, 0.0f));
            _playerForce.x = -PLAYER_START_FORCE;
        }
        else if (_playerForce.x == PLAYER_START_FORCE)
        {
            bdPlayer->applyForce(Vec2(-PLAYER_START_FORCE, 0.0f));
            bdPlayer->applyForce(Vec2(-PLAYER_START_FORCE, 0.0f));
            _playerForce.x = -PLAYER_START_FORCE;
        }
        else if (_playerForce.x == PLAYER_MOVE_FORCE)
        {
            bdPlayer->applyForce(Vec2(-PLAYER_MOVE_FORCE, 0.0f));
            bdPlayer->applyForce(Vec2(-PLAYER_START_FORCE, 0.0f));
            _playerForce.x = -PLAYER_START_FORCE;
        }
        else if (_playerForce.x == -PLAYER_START_FORCE)
        {
            if (velocity.x < -300.0f)
            {
                CCLOG("-300.0f");
                bdPlayer->applyForce(Vec2(PLAYER_START_FORCE, 0.0f));
                bdPlayer->applyForce(Vec2(-PLAYER_MOVE_FORCE, 0.0f));
                _playerForce.x = -PLAYER_MOVE_FORCE;
            }
        }
        else if (_playerForce.x == -PLAYER_MOVE_FORCE)
        {
            
        }
    }
    // Right
    else if (_continueInput == 4)
    {
        if (_playerForce.x == 0.0f)
        {
            bdPlayer->applyForce(Vec2(PLAYER_START_FORCE, 0.0f));
            _playerForce.x = PLAYER_START_FORCE;
        }
        else if (_playerForce.x == -PLAYER_START_FORCE)
        {
            bdPlayer->applyForce(Vec2(PLAYER_START_FORCE, 0.0f));
            bdPlayer->applyForce(Vec2(PLAYER_START_FORCE, 0.0f));
            _playerForce.x = PLAYER_START_FORCE;
        }
        else if (_playerForce.x == -PLAYER_MOVE_FORCE)
        {
            bdPlayer->applyForce(Vec2(PLAYER_MOVE_FORCE, 0.0f));
            bdPlayer->applyForce(Vec2(PLAYER_START_FORCE, 0.0f));
            _playerForce.x = PLAYER_START_FORCE;
        }
        else if (_playerForce.x == PLAYER_START_FORCE)
        {
            if (velocity.x > 300.0f)
            {
                CCLOG("300.0f");
                bdPlayer->applyForce(Vec2(-PLAYER_START_FORCE, 0.0f));
                bdPlayer->applyForce(Vec2(PLAYER_MOVE_FORCE, 0.0f));
                _playerForce.x = PLAYER_MOVE_FORCE;
            }
        }
        else if (_playerForce.x == PLAYER_MOVE_FORCE)
        {
            
        }
    }
    
    // CCLOG("[v:%f, %f]", velocity.x, velocity.y);
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
    if (!_controlRole || !_player) return;
    
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