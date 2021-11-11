#include "idea_facility_rope_type1_right.h"

idea_facility_rope_type1_right* idea_facility_rope_type1_right::createNew()
{
    return new idea_facility_rope_type1_right();
}

void idea_facility_rope_type1_right::destroy()
{
    delete this;
}

AnimType idea_facility_rope_type1_right::getAnimType()
{
    return AnimType::rope1;
}

idea_facility_rope_type1_right::idea_facility_rope_type1_right()
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

	animUnit->type = AnimType::rope1;
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

idea_facility_rope_type1_right::~idea_facility_rope_type1_right()
{
}