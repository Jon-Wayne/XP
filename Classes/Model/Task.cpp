#include "Task.h"

Task::Task()
{
    
}

Task::~Task()
{
    CCLOG("~Task");
    
}

Task *Task::create()
{
	auto ref = new Task();
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

bool Task::init()
{
    
    return true;
}

Clonable* Task::clone() const
{
    auto ref = Task::create();
    return ref;
}