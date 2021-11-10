#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_wall :
    public FacilityStatic
{
public:
    static idea_facility_dirt_wall* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    idea_facility_dirt_wall();
    ~idea_facility_dirt_wall();
};

