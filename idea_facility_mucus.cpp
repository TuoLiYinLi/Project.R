#include "idea_facility_mucus.h"

idea_facility_mucus* idea_facility_mucus::createNew()
{
	return new idea_facility_mucus();
}

idea_facility_mucus::idea_facility_mucus()
{
	type_facility = FacilityType::mucus;

	flag_static = false;

	name = L"ճҺ";
	science_name = L"ճҺ";
	introduction = L"ʷ��ķ���µ�һ����ճҺ��������ġ�";

	animation_type_idle = AnimationType::facility_mucus;

	health = 4;
	health_max = 4;

	physics_object->type_ally = AllyType::monster;
}

void idea_facility_mucus::onHit(Projectile* p)
{
	if(counting_container.getNumOf(CountingType::slime)>0)
	{
		counting_container.addNumOf(CountingType::slime, -1);
	}else
	{
		Facility::onHit(p);
	}
}
