#pragma once
#include "FacilityStatic.h"
class FacilityRope1R :
    public FacilityStatic
{
public:
    static FacilityRope1R* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityRope1R();
    ~FacilityRope1R();
};

