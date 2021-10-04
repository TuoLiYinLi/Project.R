#include "FacilityRopeHeadL.h"

FacilityRopeHeadL* FacilityRopeHeadL::createNew()
{
    return new FacilityRopeHeadL();
}

void FacilityRopeHeadL::destroy()
{
    delete this;
}

FacilityRopeHeadL::FacilityRopeHeadL()
{
    animUnit->flip = SDL_FLIP_HORIZONTAL; 
}

FacilityRopeHeadL::~FacilityRopeHeadL()
{
}
