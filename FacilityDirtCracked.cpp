#include "FacilityDirtCracked.h"
#include "GameToolkit.h"


FacilityDirtCracked* FacilityDirtCracked::createNew()
{
	auto f=new FacilityDirtCracked();
	return f;
}

void FacilityDirtCracked::destroy()
{
    delete this;
}

void FacilityDirtCracked::onHit(Form* form)
{
	health -= 1;
	if (health < 0) {
		health = 0;
	}
	gameToolkit::createText(x, y, "-1", { 255,255,255,255 });
}


AnimType FacilityDirtCracked::getAnimType()
{
	return AnimType::gridDirdCracked;
}

FacilityDirtCracked::FacilityDirtCracked()
{
	blockingType = BlockingType::absolute;
	ally = AllyType::neutral;
	idleLength = 0;
	activateLength = 0;
	deathLength = 0;
	width = 1;
	height = 1;
	health = 15;
	activateCycle = 0;
	activateCD = 0;

	animUnit = AnimationUnit::createNew();
	animUnit->type = AnimType::gridDirdCracked;
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

FacilityDirtCracked::~FacilityDirtCracked()
{
}
