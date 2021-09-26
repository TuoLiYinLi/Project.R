#pragma once
#include "FacilityStatic.h"
class FacilityDirtStairB :
    public FacilityStatic
{
public:
    static FacilityDirtStairB* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityDirtStairB();
    ~FacilityDirtStairB();
};

