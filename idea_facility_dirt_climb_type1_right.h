#pragma once
#include "idea_facility_dirt_climb_type1_left.h"
class idea_facility_dirt_climb_type1_right :
    public idea_facility_dirt_climb_type1_left
{
public:
    static idea_facility_dirt_climb_type1_right* createNew();
    virtual void destroy() override;

protected:
    idea_facility_dirt_climb_type1_right();
};

