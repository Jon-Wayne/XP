//
//  Item.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__Item__
#define __XP__Item__

#include "cocos2d.h"
using namespace cocos2d;

#include "ItemData.h"

class Item : public Ref, public Clonable
{
public:
    Item();
	~Item();

	static Item *create();
	bool init();
    virtual Clonable* clone() const;
private:
    Sprite      *_sprite;
    ItemData    *_data;
};

#endif /* defined(__XP__Item__) */
