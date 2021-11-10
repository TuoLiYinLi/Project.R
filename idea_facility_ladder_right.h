#pragma once
#include "idea_facility_ladder_left.h"
class idea_facility_ladder_right :
    public idea_facility_ladder_left
{
public:
    static idea_facility_ladder_right* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();
protected:
    idea_facility_ladder_right();
    ~idea_facility_ladder_right();
};

