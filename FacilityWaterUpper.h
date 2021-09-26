#pragma once
#include "FacilityDynamic.h"
class FacilityWaterUpper :
    public FacilityDynamic
{
public:
    static FacilityWaterUpper* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();
protected:
    FacilityWaterUpper();
    ~FacilityWaterUpper();
};

