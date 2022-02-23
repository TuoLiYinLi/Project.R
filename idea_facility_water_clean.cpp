#include "idea_facility_water_clean.h"
#include "Defined.h"
idea_facility_water_clean* idea_facility_water_clean::createNew()
{
	return new idea_facility_water_clean();
}

void idea_facility_water_clean::setWaterTop()
{
	animation_type_idle = top;
}

void idea_facility_water_clean::setWater()
{
	animation_type_idle = ori;
}

idea_facility_water_clean::idea_facility_water_clean()
{
	name = L"ˮ��";
	science_name = L"��ˮ";
	introduction = L"�峺��ˮ����������Ӿ�Ļ�С�ĵ㡣";
	ori = AnimationType::facility_water_clean;
	top = AnimationType::facility_water_clean_top;
	extra_depth = depth_world_chara - depth_world_facility + 128;
	getPhysics()->setFacilityType(BlockingType::liquid);
	setWater();
}
