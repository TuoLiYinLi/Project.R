#include "idea_facility_dirt_solid.h"

idea_facility_dirt_solid* idea_facility_dirt_solid::createNew()
{
	return new idea_facility_dirt_solid();
}

idea_facility_dirt_solid::idea_facility_dirt_solid()
{
	type_facility = FacilityType::dirt_solid;

	name = L"����";
	science_name = L"����";
	introduction = L"��Ӳ����������";

	getPhysics()->setFacilityType(BlockingType::solid);
	list_various_texture->push_back(AnimationType::facility_dirt_solid_1);
	list_various_texture->push_back(AnimationType::facility_dirt_solid_2);
	list_various_texture->push_back(AnimationType::facility_dirt_solid_3);
	setVariousTexture();
}
