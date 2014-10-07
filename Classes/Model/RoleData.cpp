#include "RoleData.h"

#include "DataManager.h"

RoleData::RoleData()
{
    
}

RoleData::~RoleData()
{
    
    CCLOG("~RoleData");
}

RoleData *RoleData::create()
{
	auto ref = new RoleData();
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

RoleData *RoleData::create(U32 dataId)
{
    auto ref = RoleData::create();
    ref->init(dataId);
    return ref;
}

bool RoleData::init()
{
    
    return init(0);
}

bool RoleData::init(U32 dataId)
{
    if (dataId == 0) return true;
    
    auto dm = DataManager::getInstance();
    auto dataItem = dm->getDataItem("Role", dataId);
    if (!dataItem) return true;
    
    U8 index = -1;
    data.dataId = dataId;
    data.type = (RoleType)dataItem->at(++index).asByte();
    data.sex = (SexType)dataItem->at(++index).asByte();
    data.name = dataItem->at(++index).asString();
    data.status = (U32)dataItem->at(++index).asInt();
    data.icon = dataItem->at(++index).asString();
    data.picture = dataItem->at(++index).asString();
    data.animation = dataItem->at(++index).asString();
    data.physics = dataItem->at(++index).asString();
    data.isCanRotate = dataItem->at(++index).asBool();
    data.velocityLimit = dataItem->at(++index).asFloat();
    
    return true;
}

Clonable* RoleData::clone() const
{
    auto ref = RoleData::create();
    
    // @todo copy variables
    
    return ref;
}