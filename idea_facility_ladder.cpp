#include "idea_facility_ladder.h"

idea_facility_ladder* idea_facility_ladder::createNew()
{
	return new idea_facility_ladder();
}

idea_facility_ladder::idea_facility_ladder()
{
	name = L"ÅÀÌÝ";

	getPhysicsFacility()->setFacilityType(BlockingType::support);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_1);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_2);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_3);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_4);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_5);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_6);
	setVariousTexture();
}

idea_facility_ladder::~idea_facility_ladder()
{
}
