#include "FacilityRopeTailL.h"

FacilityRopeTailL* FacilityRopeTailL::createNew()
{
    return new FacilityRopeTailL();
}

void FacilityRopeTailL::destroy()
{
    delete this;
}

FacilityRopeTailL::FacilityRopeTailL()
{
    animUnit->flip = SDL_FLIP_HORIZONTAL;
    animUnit->type=AnimType::ropeTail;
}
