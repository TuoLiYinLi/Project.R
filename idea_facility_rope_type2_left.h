#pragma once
#include "idea_facility_rope_type2_right.h"
class idea_facility_rope_type2_left :
    public idea_facility_rope_type2_right
{
public:
    static idea_facility_rope_type2_left* createNew();
    virtual void destroy();

protected:
    idea_facility_rope_type2_left();
};

