#pragma once
#include "FacilityDynamic.h"
class idea_facility_water_upper :
    public FacilityDynamic
{
public:
    static idea_facility_water_upper* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();
protected:
    idea_facility_water_upper();
    ~idea_facility_water_upper();
};

