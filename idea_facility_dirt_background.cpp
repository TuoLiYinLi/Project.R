#include "idea_facility_dirt_background.h"

idea_facility_dirt_background* idea_facility_dirt_background::createNew()
{
	auto facility = new idea_facility_dirt_background();
	if (facility == nullptr) {
#ifdef _DEBUG
		std::cout << "\t\tERROR:new idea_facility_dirt_background()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr\n";
#endif // _DEBUG
	}

	return facility;
}

void idea_facility_dirt_background::destroy()
{
	delete this;
}


AnimType idea_facility_dirt_background::getAnimType()
{
	return AnimType::gridDirt_1n;
}

idea_facility_dirt_background::idea_facility_dirt_background()
{
	blockingType = BlockingType::no;
	idleLength = 0;
	activateLength = 0;
	width = 1;
	height = 1;
	health = 100;
	activateCycle = 0;
	activateCD = 0;

	animUnit = AnimationUnit::createNew();
	animUnit->type = AnimType::gridDirt_1n;
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

idea_facility_dirt_background::~idea_facility_dirt_background() = default;

