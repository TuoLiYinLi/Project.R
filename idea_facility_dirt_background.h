#pragma once
#include "FacilityVarious.h"
class idea_facility_dirt_background :
    public FacilityVarious
{
public:
	static  idea_facility_dirt_background* createNew();

protected:
	idea_facility_dirt_background();
	~idea_facility_dirt_background()override;
};

