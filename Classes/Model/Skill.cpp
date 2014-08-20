#include "Skill.h"

Skill::Skill()
{
    
}

Skill::~Skill()
{
    CCLOG("~Skill");
    
}

Skill *Skill::create()
{
	auto ref = new Skill();
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

bool Skill::init()
{
    
    return true;
}

Clonable* Skill::clone() const
{
    auto ref = Skill::create();
    return ref;
}