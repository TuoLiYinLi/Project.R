#pragma once
#include "FacilityStatic.h"
class FacilityDirtWall :
    public FacilityStatic
{
public:
    static FacilityDirtWall* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityDirtWall();
    ~FacilityDirtWall();
};

