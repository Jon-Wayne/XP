#include "TaskData.h"

TaskData::TaskData()
{
    
}

TaskData::~TaskData()
{
    CCLOG("~TaskData");
    
}

TaskData *TaskData::create()
{
	auto ref = new TaskData();
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

bool TaskData::init()
{
    
    return true;
}

Clonable* TaskData::clone() const
{
    auto ref = TaskData::create();
    return ref;
}