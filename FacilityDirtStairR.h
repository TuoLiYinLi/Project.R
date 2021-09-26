#pragma once
#include "FacilityStatic.h"
class FacilityDirtStairR :
    public FacilityStatic
{
public:
    static FacilityDirtStairR* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityDirtStairR();
    ~FacilityDirtStairR();
};

