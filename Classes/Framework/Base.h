#ifndef __BASE_H__
#define __BASE_H__

#include "cocos2d.h"
using namespace cocos2d;

class RefNULL : public Ref
{
public:
    RefNULL(){};
    ~RefNULL(){};
};

static RefNULL refNULL;
static RefNULL *NULL_ = &refNULL;

#endif //__BASE_H__