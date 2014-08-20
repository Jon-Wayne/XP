#include "ItemData.h"

ItemData::ItemData()
{
    
}

ItemData::~ItemData()
{
    CCLOG("~ItemData");
    
}

ItemData *ItemData::create()
{
	auto ref = new ItemData();
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

bool ItemData::init()
{
    
    return true;
}

Clonable* ItemData::clone() const
{
    auto ref = ItemData::create();
    return ref;
}