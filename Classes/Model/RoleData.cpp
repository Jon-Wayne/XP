#include "RoleData.h"

RoleData::RoleData()
{
    
}

RoleData::~RoleData()
{
    
    CCLOG("~RoleData");
}

RoleData *RoleData::create()
{
	auto ref = new RoleData();
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

static RoleData *create(U32 dataId)
{
    auto ref = RoleData::create();
    ref->init(dataId);
    return ref;
}

bool RoleData::init()
{
    
    return init(0);
}

bool RoleData::init(U32 dataId)
{
    
    return true;
}

Clonable* RoleData::clone() const
{
    auto ref = RoleData::create();
    
    // @todo copy variables
    
    return ref;
}