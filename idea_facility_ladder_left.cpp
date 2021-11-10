#include "idea_facility_ladder_left.h"

idea_facility_ladder_left* idea_facility_ladder_left::createNew()
{
    auto fl = new idea_facility_ladder_left();
    return fl;
}

void idea_facility_ladder_left::destroy()
{
    delete this;
}

AnimType idea_facility_ladder_left::getAnimType()
{
    return AnimType::ladder;
}

idea_facility_ladder_left::idea_facility_ladder_left()
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

	animUnit->type = AnimType::ladder;
	animUnit->depth = 5;
	animUnit->deltaX = 0;
	animUnit->deltaY = 0;
	animUnit->x = this->x;
	animUnit->y = this->y;
	animUnit->angle = 0;
	animUnit->flip = SDL_FLIP_NONE;
	animUnit->height = height * 32;
	animUnit->width = height * 32;
}

idea_facility_ladder_left::~idea_facility_ladder_left()
{
}
