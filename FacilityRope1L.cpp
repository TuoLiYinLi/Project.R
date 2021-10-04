#include "FacilityRope1L.h"

FacilityRope1L* FacilityRope1L::createNew()
{
	return new FacilityRope1L();
}

void FacilityRope1L::destroy()
{
	delete this;
}

FacilityRope1L::FacilityRope1L()
{
	animUnit->flip = SDL_FLIP_HORIZONTAL;
}
