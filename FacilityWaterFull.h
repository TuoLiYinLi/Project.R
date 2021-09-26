#pragma once
#include "FacilityDynamic.h"
class FacilityWaterFull :
    public FacilityDynamic
{
public:
    static FacilityWaterFull* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();
protected:
    FacilityWaterFull();
    ~FacilityWaterFull();
};

