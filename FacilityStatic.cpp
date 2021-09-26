#include "FacilityStatic.h"

FacilityStatic::FacilityStatic()
{
	FacilitySystem::getInstance()->facilityList_static->push_back(this);
	ally = AllyType::peace;
}
