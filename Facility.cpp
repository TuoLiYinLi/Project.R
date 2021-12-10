#include "Facility.h"
#include "SDL.h"
#include "PhysicsFacility.h"

Facility* Facility::createNew() {
	auto const f = new Facility();
	if (!f) {
		SDL_Log(u8"警告 分配Facility内存不足");
	}
	return f;
}

Facility::Facility() {

	name = u8"default facility";

	state = FacilityState::idle;
	animation_progress = 0;
	type_game_object = GameObjectType::default_facility;

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

}



void Facility::update()
{
	
}
