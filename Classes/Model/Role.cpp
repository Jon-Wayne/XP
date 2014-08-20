#include "Role.h"

Role::Role()
{
    
}

Role::~Role()
{
    CC_SAFE_RELEASE_NULL(_sprite);
    CC_SAFE_RELEASE_NULL(_data);
    
    CCLOG("~Role");
}

Role *Role::create()
{
	auto ref = new Role();
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

static Role *create(RoleData *data)
{
    auto ref = Role::create();
    ref->init(data);
    return ref;
}

static Role *create(U32 dataId)
{
    auto ref = Role::create();
    ref->init(dataId);
    return ref;
}

bool Role::init()
{
    return init(nullptr);
}

bool Role::init(RoleData *data)
{
    _sprite = Sprite::create();
    _sprite->retain();
    
    setData(data);
    
    return true;
}

bool Role::init(U32 dataId)
{
    RoleData *data = RoleData::create(dataId);
    return init(data);
}

Clonable* Role::clone() const
{
    auto ref = Role::create();
    
    // @todo copy variables
    
    return ref;
}

void Role::setSprite(Sprite *sprite)
{
    if (_sprite != sprite)
    {
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE_NULL(_sprite);
        _sprite = sprite;
    }
}

Sprite *Role::getSprite()
{
    return _sprite;
}

void Role::setData(RoleData *data)
{
    if (_data != data)
    {
        CC_SAFE_RETAIN(data);
        CC_SAFE_RELEASE_NULL(_data);
        _data = data;
    }
}

RoleData *Role::getData()
{
    return _data;
}