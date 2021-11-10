#pragma once
#include "idea_facility_rope_tail_right.h"
class idea_facility_rope_tail_left :
    public idea_facility_rope_tail_right
{
public:
    static idea_facility_rope_tail_left* createNew();
    virtual void destroy();

protected:
    idea_facility_rope_tail_left();
};

