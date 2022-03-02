#include "idea_facility_dirt_cracked.h"

idea_facility_dirt_cracked* idea_facility_dirt_cracked::createNew()
{
	return new idea_facility_dirt_cracked();
}

idea_facility_dirt_cracked::idea_facility_dirt_cracked()
{
	type_facility = FacilityType::dirt_cracked;

	name = L"����";
	science_name = L"���ѵ�����";
	introduction = L"�������������ȥ��̫�ι̣���΢����һ�¡�";

	getPhysics()->type_ally = AllyType::neutral;
	getPhysics()->setFacilityType(BlockingType::solid);
	list_various_texture->push_back(AnimationType::facility_soil_cracked_1);
	list_various_texture->push_back(AnimationType::facility_soil_cracked_2);
	list_various_texture->push_back(AnimationType::facility_soil_cracked_3);
	list_various_texture->push_back(AnimationType::facility_soil_cracked_4);
	setVariousTexture();
}
