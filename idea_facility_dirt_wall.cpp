#include "idea_facility_dirt_wall.h"
#include "Defined.h"

idea_facility_dirt_wall* idea_facility_dirt_wall::createNew()
{
	auto f = new idea_facility_dirt_wall();
	if (f==nullptr) {
#ifdef _DEBUG
		std::cout << "\t\tERROR:new idea_facility_dirt_wall()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr\n";
#endif // _DEBUG
	}

	return f;
}

void idea_facility_dirt_wall::destroy() {
	delete this;
}

AnimType idea_facility_dirt_wall::getAnimType()
{
	return AnimType::gridDirt_1a;
}


idea_facility_dirt_wall::idea_facility_dirt_wall() {
	blockingType = BlockingType::absolute;
	idleLength = 0;
	activateLength = 0;
	width = 1;
	height = 1;
	health = 100;
	activateCycle = 0;
	activateCD = 0;

	animUnit = AnimationUnit::createNew();

	animUnit->type = AnimType::gridDirt_1a;
	animUnit->depth = 0;
	animUnit->deltaX = 0;
	animUnit->deltaY = 0;
	animUnit->x = this->x;
	animUnit->y = this->y;
	animUnit->angle = 0;
	animUnit->flip = SDL_FLIP_NONE;
	animUnit->height = height * 32;
	animUnit->width = height * 32;
}

idea_facility_dirt_wall::~idea_facility_dirt_wall() = default;