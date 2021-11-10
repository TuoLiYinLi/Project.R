#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_stair_left :
    public FacilityStatic
{
public:
    static idea_facility_dirt_stair_left* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    idea_facility_dirt_stair_left();
    ~idea_facility_dirt_stair_left();
};

