#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_climb_type1_left :
    public FacilityStatic
{
public:
    static idea_facility_dirt_climb_type1_left* createNew();
    virtual void destroy() override;

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType()override;
protected:
    idea_facility_dirt_climb_type1_left();
    ~idea_facility_dirt_climb_type1_left();
};

