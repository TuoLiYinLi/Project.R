#include "idea_facility_dirt_background.h"

idea_facility_dirt_background* idea_facility_dirt_background::createNew()
{
	return new idea_facility_dirt_background();
}

idea_facility_dirt_background::idea_facility_dirt_background()
{
	name = L"泥土背景";
	science_name = L"泥土";
	introduction = L"泥巴、石头……";

	getPhysics()->setFacilityType(BlockingType::solid);
	list_various_texture->push_back(AnimationType::facility_dirt_background_1);
	list_various_texture->push_back(AnimationType::facility_dirt_background_2);
	list_various_texture->push_back(AnimationType::facility_dirt_background_3);
	list_various_texture->push_back(AnimationType::facility_dirt_background_4);
	list_various_texture->push_back(AnimationType::facility_dirt_background_5);
	list_various_texture->push_back(AnimationType::facility_dirt_background_6);
	list_various_texture->push_back(AnimationType::facility_dirt_background_7);
	list_various_texture->push_back(AnimationType::facility_dirt_background_8);
	setVariousTexture();
}

idea_facility_dirt_background::~idea_facility_dirt_background()
{
	
}
