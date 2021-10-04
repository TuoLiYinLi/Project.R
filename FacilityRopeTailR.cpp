#include "FacilityRopeTailR.h"

FacilityRopeTailR* FacilityRopeTailR::createNew()
{
    return new FacilityRopeTailR();
}

void FacilityRopeTailR::destroy()
{
    delete this;
}

AnimType FacilityRopeTailR::getAnimType()
{
    return AnimType::ropeTail;
}

FacilityRopeTailR::FacilityRopeTailR()
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

	animUnit->type = AnimType::ropeTail;
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

FacilityRopeTailR::~FacilityRopeTailR()
{
}
