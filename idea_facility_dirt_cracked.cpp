#include "idea_facility_dirt_cracked.h"

idea_facility_dirt_cracked* idea_facility_dirt_cracked::createNew()
{
	return new idea_facility_dirt_cracked();
}

idea_facility_dirt_cracked::idea_facility_dirt_cracked()
{
	type_facility = FacilityType::dirt_cracked;

	name = L"泥土";
	science_name = L"碎裂的泥土";
	introduction = L"这里的泥土看上去不太牢固，稍微留意一下。";

	getPhysics()->type_ally = AllyType::neutral;
	getPhysics()->setFacilityType(BlockingType::solid);
	list_various_texture->push_back(AnimationType::facility_soil_cracked_1);
	list_various_texture->push_back(AnimationType::facility_soil_cracked_2);
	list_various_texture->push_back(AnimationType::facility_soil_cracked_3);
	list_various_texture->push_back(AnimationType::facility_soil_cracked_4);
	setVariousTexture();
}
