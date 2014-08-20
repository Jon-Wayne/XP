//
//  ItemData.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__ItemData__
#define __XP__ItemData__

#define     NAME_MAX_LENGTH     20
#define     SKILL_MAX_NUM       50
#define     ITEM_MAX_NUM        50

#include "cocos2d.h"
using namespace cocos2d;

#include "../type.h"

typedef enum _ItemType
{
    ItemTypePlayer,
    ItemTypeNPC,
} ItemType;

/*
 *  final convenient common data struct,
 *  consist of base data, template data,
 *  dynamic data.
 */
struct stItemData
{
    /*
     *  base
     */
    U32         dataId;
    ItemType    type;
    U32         sex;
    UTF8        name[NAME_MAX_LENGTH];
    U32         skills[SKILL_MAX_NUM];  // not sure if this is needed.
    U32         itemsId[ITEM_MAX_NUM];  // not sure if this is needed.
    
    /*
     *  physic
     */
    F32         mass;
    F32         width;
    F32         height;
    F32         Radian;
};

class ItemData : public Ref, public Clonable
{
public:
    ItemData();
    ~ItemData();
    
    static ItemData *create();
	bool init();
    virtual Clonable* clone() const;
    
    void incode();
    void decode();
private:
    stItemData data;
};

#endif /* defined(__XP__ItemData__) */
