#include "SkillData.h"

SkillData::SkillData()
{
    
}

SkillData::~SkillData()
{
    CCLOG("~SkillData");
    
}

SkillData *SkillData::create()
{
	auto ref = new SkillData();
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

bool SkillData::init()
{
    
    return true;
}

Clonable* SkillData::clone() const
{
    auto ref = SkillData::create();
    return ref;
}