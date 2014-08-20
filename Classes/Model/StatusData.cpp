#include "StatusData.h"

StatusData::StatusData()
{
    
}

StatusData::~StatusData()
{
    CCLOG("~StatusData");
    
}

StatusData *StatusData::create()
{
	auto ref = new StatusData();
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

bool StatusData::init()
{
    
    return true;
}

Clonable* StatusData::clone() const
{
    auto ref = StatusData::create();
    return ref;
}