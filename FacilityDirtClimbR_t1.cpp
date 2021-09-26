#include "FacilityDirtClimbR_t1.h"

FacilityDirtClimbR_t1* FacilityDirtClimbR_t1::createNew()
{
    return new FacilityDirtClimbR_t1();
}

void FacilityDirtClimbR_t1::destroy()
{
    delete this;
}

FacilityDirtClimbR_t1::FacilityDirtClimbR_t1()
{
    animUnit->flip = SDL_FLIP_HORIZONTAL;
}

