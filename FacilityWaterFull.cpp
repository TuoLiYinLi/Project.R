#include "FacilityWaterFull.h"

FacilityWaterFull* FacilityWaterFull::createNew()
{
    auto f = new FacilityWaterFull();
    return f;
}

void FacilityWaterFull::destroy()
{
    delete this;
}

AnimType FacilityWaterFull::getAnimType()
{
	return AnimType::gridWater_1full;
}

FacilityWaterFull::FacilityWaterFull()
{
	blockingType = BlockingType::liquid;
	ally = AllyType::peace;
	idleLength = 0;
	activateLength = 0;
	deathLength = 0;
	width = 1;
	height = 1;
	health = 100;
	activateCycle = 0;
	activateCD = 0;

	animUnit = AnimationUnit::createNew();
	animUnit->type = AnimType::gridWater_1full;
	animUnit->depth = 2;
	animUnit->deltaX = 0;
	animUnit->deltaY = 0;
	animUnit->x = this->x;
	animUnit->y = this->y;
	animUnit->angle = 0;
	animUnit->flip = SDL_FLIP_NONE;
	animUnit->height = height * 32;
	animUnit->width = height * 32;
}

FacilityWaterFull::~FacilityWaterFull()
{
}
