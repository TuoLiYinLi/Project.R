#include "FacilityRope2L.h"

FacilityRope2L* FacilityRope2L::createNew()
{
    return new FacilityRope2L();
}

void FacilityRope2L::destroy()
{
    delete this;
}

FacilityRope2L::FacilityRope2L()
{
	animUnit->type = AnimType::rope2;
	animUnit->flip = SDL_FLIP_HORIZONTAL;
}
