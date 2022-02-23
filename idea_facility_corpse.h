#pragma once
#include "Facility.h"
class idea_facility_corpse :
    public Facility
{
public:
    static idea_facility_corpse* createNew();
protected:
    idea_facility_corpse();
};

