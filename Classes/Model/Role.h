//
//  Role.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__Role__
#define __XP__Role__

#include "cocos2d.h"
using namespace cocos2d;

#include "RoleData.h"

class Role : public Ref, public Clonable
{
public:
    Role();
	~Role();
    
	static Role *create();
    static Role *create(RoleData *data);
    static Role *create(U32 dataId);
	bool init();
    bool init(RoleData *data);
    bool init(U32 dataId);
    virtual Clonable* clone() const;
    
    void setSprite(Sprite *sprite);
    Sprite *getSprite();
    
    void setData(RoleData *data);
    RoleData *getData();
private:
    Sprite      *_sprite;
    RoleData    *_data;
};

#endif /* defined(__XP__Role__) */
