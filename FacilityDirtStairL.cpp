#include "FacilityDirtStairL.h"

FacilityDirtStairL* FacilityDirtStairL::createNew()
{
    return new FacilityDirtStairL();
}

void FacilityDirtStairL::destroy()
{
    delete this;
}

AnimType FacilityDirtStairL::getAnimType()
{
	return AnimType::gridDirtStair_1L;
}



FacilityDirtStairL::FacilityDirtStairL()
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

FacilityDirtStairL::~FacilityDirtStairL()
{
}
