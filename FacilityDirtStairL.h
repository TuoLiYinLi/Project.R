#pragma once
#include "FacilityStatic.h"
class FacilityDirtStairL :
    public FacilityStatic
{
public:
    static FacilityDirtStairL* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityDirtStairL();
    ~FacilityDirtStairL();
};

