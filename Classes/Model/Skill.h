//
//  Skill.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__Skill__
#define __XP__Skill__

#include "cocos2d.h"
using namespace cocos2d;

#include "SkillData.h"

class Skill : public Ref, public Clonable
{
public:
    Skill();
	~Skill();

	static Skill *create();
	bool init();
    virtual Clonable* clone() const;
private:
    Sprite      *_sprite;
    SkillData    *_data;
};

#endif /* defined(__XP__Skill__) */
