#include "FacilityLadderR.h"

FacilityLadderR* FacilityLadderR::createNew()
{
	auto f = new FacilityLadderR();
	return f;
}

void FacilityLadderR::destroy()
{
	delete this;
}

AnimType FacilityLadderR::getAnimType()
{
	return AnimType::ladder;
}

FacilityLadderR::FacilityLadderR()
{
	animUnit->flip = SDL_FLIP_HORIZONTAL;
}

FacilityLadderR::~FacilityLadderR()
{
}
