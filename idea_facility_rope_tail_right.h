#pragma once
#include "FacilityStatic.h"
class idea_facility_rope_tail_right :
    public FacilityStatic
{
public:
    static idea_facility_rope_tail_right* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    idea_facility_rope_tail_right();
    ~idea_facility_rope_tail_right();
};

