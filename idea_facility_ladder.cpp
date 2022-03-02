#include "idea_facility_ladder.h"

idea_facility_ladder* idea_facility_ladder::createNew()
{
	return new idea_facility_ladder();
}

idea_facility_ladder::idea_facility_ladder()
{
	type_facility = FacilityType::ladder;

	name = L"����";
	science_name = L"ľ����";
	introduction = L"�����ڴ�ֱ�ƶ������ӣ��������õġ�";

	getPhysics()->setFacilityType(BlockingType::support);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_1);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_2);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_3);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_4);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_5);
	list_various_texture->push_back(AnimationType::facility_ladder_wooden_6);
	setVariousTexture();
}
