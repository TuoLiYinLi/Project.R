#include "Facility.h"
#include "SDL.h"
#include "PhysicsFacility.h"

Facility* Facility::createNew() {
	return new Facility();
}

int Facility::facility_num = 0;

int Facility::getFacilityNum()
{
	return facility_num;
}


Facility::Facility() {
	facility_num++;

	name = u8"default facility";
	type_game_object = GameObjectType::default_facility;

	state = FacilityState::idle;
	animation_progress = 0;

	animation_length_idle = 0;
	animation_length_activated = 0;
	animation_length_death = 0;

	health = 10;

	//绑定物理设施
	physics_object = PhysicsFacility::createNew();
	physics_object->game_object = this;

	physics_object->bodyX = 1;
	physics_object->bodyY = 1;

}


Facility::~Facility() {
	facility_num--;
}



void Facility::update()
{
	
}
