#include "RoleManager.h"

static RoleManager *s_roleManager = nullptr;

RoleManager::RoleManager():
_target(nullptr)
{
    
}

RoleManager::~RoleManager()
{
    CCLOG("~RoleManager");
    
}

RoleManager *RoleManager::getInstance()
{
    if (!s_roleManager)
    {
        s_roleManager = new RoleManager();
        if (s_roleManager->init())
        {
            s_roleManager->retain();
        }
        else
        {
            CC_SAFE_DELETE(s_roleManager);
        }
    }
    
    return s_roleManager;
}

bool RoleManager::init()
{
    return true;
}

void RoleManager::addRole(Role *role)
{
    _roles.pushBack(role);
    
    _target->addChild(role->getSprite());
}

void RoleManager::addRole(U32 dataId)
{
    auto role = Role::create(dataId);
    addRole(role);
}