#pragma once
#include "FacilityStatic.h"
class FacilityRope2R :
    public FacilityStatic
{
public:
    static FacilityRope2R* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityRope2R();
    ~FacilityRope2R();
};

