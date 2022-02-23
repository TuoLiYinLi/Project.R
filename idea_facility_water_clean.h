#pragma once
#include "Facility.h"
class idea_facility_water_clean :
    public Facility
{

public:
	static idea_facility_water_clean* createNew();
	void setWaterTop();
	void setWater();
	
protected:
	idea_facility_water_clean();

	AnimationType ori;
	AnimationType top;
};

