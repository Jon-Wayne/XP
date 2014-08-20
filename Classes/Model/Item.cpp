#include "Item.h"

Item::Item()
{
    
}

Item::~Item()
{
    CCLOG("~Item");
    
}

Item *Item::create()
{
	auto ref = new Item();
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

bool Item::init()
{
    
    return true;
}

Clonable* Item::clone() const
{
    auto ref = Item::create();
    return ref;
}