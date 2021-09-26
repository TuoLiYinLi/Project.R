#include "FacilityDirtWall.h"
#include "Defined.h"

FacilityDirtWall* FacilityDirtWall::createNew()
{
	auto f = new FacilityDirtWall();
	if (f==nullptr) {
#ifdef _DEBUG
		std::cout << "\t\tERROR:new FacilityDirtWall()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr\n";
#endif // _DEBUG
	}

	return f;
}

void FacilityDirtWall::destroy() {
	delete this;
}

AnimType FacilityDirtWall::getAnimType()
{
	return AnimType::gridDirt_1a;
}


FacilityDirtWall::FacilityDirtWall() {
	blockingType = BlockingType::absolute;
	idleLength = 0;
	activateLength = 0;
	width = 1;
	height = 1;
	health = 100;
	activateCycle = 0;
	activateCD = 0;

	animUnit = AnimationUnit::createNew();

	animUnit->type = AnimType::gridDirt_1a;
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

FacilityDirtWall::~FacilityDirtWall() {
	
}