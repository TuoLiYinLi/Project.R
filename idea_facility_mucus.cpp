#include "idea_facility_mucus.h"

idea_facility_mucus* idea_facility_mucus::createNew()
{
	return new idea_facility_mucus();
}

idea_facility_mucus::idea_facility_mucus()
{
	type_facility = FacilityType::mucus;

	flag_static = false;

	name = L"Õ³Òº";
	science_name = L"Õ³Òº";
	introduction = L"Ê·À³Ä·ÁôÏÂµÄÒ»´óÍÅÕ³Òº£¬ÔàÙâÙâµÄ¡£";

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
