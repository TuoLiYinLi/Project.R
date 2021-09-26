#include "FacilityDirtClimbL_t1.h"

FacilityDirtClimbL_t1* FacilityDirtClimbL_t1::createNew()
{
    return new FacilityDirtClimbL_t1();
}

void FacilityDirtClimbL_t1::destroy()
{
	delete this;
}

AnimType FacilityDirtClimbL_t1::getAnimType()
{
    return AnimType::gridDirtClimb_L_t1;
}

FacilityDirtClimbL_t1::FacilityDirtClimbL_t1()
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

	animUnit->type = AnimType::gridDirtClimb_L_t1;
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

FacilityDirtClimbL_t1::~FacilityDirtClimbL_t1()
{
}
