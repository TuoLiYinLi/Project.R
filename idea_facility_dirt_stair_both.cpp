#include "idea_facility_dirt_stair_both.h"

idea_facility_dirt_stair_both* idea_facility_dirt_stair_both::createNew()
{
    return new idea_facility_dirt_stair_both();
}

void idea_facility_dirt_stair_both::destroy()
{
    delete this;
}

AnimType idea_facility_dirt_stair_both::getAnimType()
{
	return AnimType::gridDirtStair_1B;
}

idea_facility_dirt_stair_both::idea_facility_dirt_stair_both()
{
	blockingType = BlockingType::supportive;
	idleLength = 0;
	activateLength = 0;
	width = 1;
	height = 1;
	health = 100;
	activateCycle = 0;
	activateCD = 0;

	animUnit = AnimationUnit::createNew();

	animUnit->type = AnimType::gridDirtStair_1B;
	animUnit->depth = 1;
	animUnit->deltaX = 0;
	animUnit->deltaY = 0;
	animUnit->x = this->x;
	animUnit->y = this->y;
	animUnit->angle = 0;
	animUnit->flip = SDL_FLIP_NONE;
	animUnit->height = height * 32;
	animUnit->width = height * 32;
}

idea_facility_dirt_stair_both::~idea_facility_dirt_stair_both() = default;