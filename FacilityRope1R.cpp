#include "FacilityRope1R.h"

FacilityRope1R* FacilityRope1R::createNew()
{
    return new FacilityRope1R();
}

void FacilityRope1R::destroy()
{
    delete this;
}

AnimType FacilityRope1R::getAnimType()
{
    return AnimType::rope1;
}

FacilityRope1R::FacilityRope1R()
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

FacilityRope1R::~FacilityRope1R()
{
}
