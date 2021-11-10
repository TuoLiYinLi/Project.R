#include "idea_facility_dirt_stair_left.h"

idea_facility_dirt_stair_left* idea_facility_dirt_stair_left::createNew()
{
    return new idea_facility_dirt_stair_left();
}

void idea_facility_dirt_stair_left::destroy()
{
    delete this;
}

AnimType idea_facility_dirt_stair_left::getAnimType()
{
	return AnimType::gridDirtStair_1L;
}



idea_facility_dirt_stair_left::idea_facility_dirt_stair_left()
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

	animUnit->type = AnimType::gridDirtStair_1L;
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

idea_facility_dirt_stair_left::~idea_facility_dirt_stair_left() = default;
