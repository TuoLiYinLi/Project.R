#include "FacilityRope2R.h"

FacilityRope2R* FacilityRope2R::createNew()
{
    return new FacilityRope2R();
}

void FacilityRope2R::destroy()
{
    delete this;
}

AnimType FacilityRope2R::getAnimType()
{
    return AnimType::rope2;
}

FacilityRope2R::FacilityRope2R()
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

	animUnit->type = AnimType::rope2;
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

FacilityRope2R::~FacilityRope2R()
{
}
