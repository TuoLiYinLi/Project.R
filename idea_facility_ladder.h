#pragma once
#include "FacilityVarious.h"

class idea_facility_ladder :
    public FacilityVarious
{
public:
	static idea_facility_ladder* createNew();
private:
	idea_facility_ladder();
	~idea_facility_ladder()override;
};

