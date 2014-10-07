//
//  RoleData.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__RoleData__
#define __XP__RoleData__

#define     NAME_MAX_LENGTH     20
#define     SKILL_MAX_NUM       50
#define     ITEM_MAX_NUM        50

#include "cocos2d.h"
using namespace cocos2d;

#include "../type.h"

typedef enum _RoleType
{
    RoleTypeStatic,
    RoleTypePlayer,
    RoleTypeNPC,
} RoleType;

typedef enum _SexType
{
    SexTypeNone,
    SexTypeMale,
    SexTypeFamale,
} SexType;

/*
 *  final convenient common data struct,
 *  consist of base data, template data,
 *  dynamic data.
 */
struct stRoleData
{
    /*
     *  base
     */
    U32         dataId;
    RoleType    type;
    SexType     sex;
    STR         name;
    U32         status;
    
    /*
     *  view
     */
    STR         icon;           // .plist file name. icon of the role, is avatar generally.
    STR         picture;        // .plist file name. static original painting.
    STR         animation;      // .ani file name. the prefix of animation name, there is a naming rule to all kinds of animation of the role.
    
    /*
     *  physic
     */
    STR         physics;        // .plist file name. exportted from PE.
    B8          isCanRotate;
    F32         velocityLimit;
    
    // not sure if those are needed.
    F32         mass;
    F32         width;
    F32         radian;
    U8          group;
    F32         density;
    F32         restitution;
    F32         friction;
    
    
    stRoleData():
    dataId(0),
    type(RoleTypeStatic),
    physics(""),
    isCanRotate(true),
    velocityLimit(INFINITY)
    {}
};

class RoleData : public Ref, public Clonable
{
public:
    RoleData();
    ~RoleData();
    
    static RoleData *create();
    static RoleData *create(U32 dataId);
	bool init();
    bool init(U32 dataId);
    virtual Clonable* clone() const;
    
    void incode();
    void decode();
public:
    stRoleData data;
};

#endif /* defined(__XP__RoleData__) */
