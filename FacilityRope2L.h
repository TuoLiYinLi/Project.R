#pragma once
#include "FacilityRope2R.h"
class FacilityRope2L :
    public FacilityRope2R
{
public:
    static FacilityRope2L* createNew();
    virtual void destroy();

protected:
    FacilityRope2L();
};

