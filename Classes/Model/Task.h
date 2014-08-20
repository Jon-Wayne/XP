//
//  Task.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__Task__
#define __XP__Task__

#include "cocos2d.h"
using namespace cocos2d;

#include "TaskData.h"

class Task : public Ref, public Clonable
{
public:
    Task();
	~Task();

	static Task *create();
	bool init();
    virtual Clonable* clone() const;
private:
    Sprite      *_sprite;
    TaskData    *_data;
};

#endif /* defined(__XP__Task__) */
