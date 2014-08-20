//
//  RoleManager.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__RoleManager__
#define __XP__RoleManager__

#include "cocos2d.h"
using namespace cocos2d;

#include "Role.h"

class RoleManager : public Ref
{
public:
    RoleManager();
	~RoleManager();

	static RoleManager *getInstance();
	bool init();
    
    void setTarget(Node *target){ _target = target; }
    Node *getTarget(){ return _target; }
    
    void addRole(Role *role);
    void addRole(U32 dataId);
private:
    
private:
    Node            *_target;
    
    Vector<Role *>  _roles;
    
};

#endif /* defined(__XP__RoleManager__) */
