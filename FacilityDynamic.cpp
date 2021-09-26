#include "FacilityDynamic.h"
#include "GameToolkit.h"

FacilityDynamic::FacilityDynamic()
{
	FacilitySystem::getInstance()->facilityList_dynamic->push_back(this);
}
