#pragma once
#include "FacilityStatic.h"
class FacilityDirtClimbL_t1 :
    public FacilityStatic
{
public:
    static FacilityDirtClimbL_t1* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();
protected:
    FacilityDirtClimbL_t1();
    ~FacilityDirtClimbL_t1();
};

