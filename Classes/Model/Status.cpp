#include "Status.h"

Status::Status()
{
    
}

Status::~Status()
{
    CCLOG("~Status");
    
}

Status *Status::create()
{
	auto ref = new Status();
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

bool Status::init()
{
    
    return true;
}

Clonable* Status::clone() const
{
    auto ref = Status::create();
    return ref;
}