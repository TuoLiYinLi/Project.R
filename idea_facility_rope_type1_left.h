#pragma once
#include "idea_facility_rope_type1_right.h"
class idea_facility_rope_type1_left :
    public idea_facility_rope_type1_right
{
public:
    static idea_facility_rope_type1_left* createNew();
    virtual void destroy();

protected:
    idea_facility_rope_type1_left();
};

