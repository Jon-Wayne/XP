//
//  Status.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__Status__
#define __XP__Status__

#include "cocos2d.h"
using namespace cocos2d;

#include "StatusData.h"

class Status : public Ref, public Clonable
{
public:
    Status();
	~Status();

	static Status *create();
	bool init();
    virtual Clonable* clone() const;
private:
    Sprite      *_sprite;
    StatusData    *_data;
};

#endif /* defined(__XP__Status__) */
