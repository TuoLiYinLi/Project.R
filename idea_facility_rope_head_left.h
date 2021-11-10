#pragma once
#include "idea_facility_rope_head_right.h"
class idea_facility_rope_head_left :
    public idea_facility_rope_head_right
{
public:
    static idea_facility_rope_head_left* createNew();
    virtual void destroy();

protected:
    idea_facility_rope_head_left();
    ~idea_facility_rope_head_left();
};

