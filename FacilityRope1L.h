#pragma once
#include "FacilityRope1R.h"
class FacilityRope1L :
    public FacilityRope1R
{
public:
    static FacilityRope1L* createNew();
    virtual void destroy();

protected:
    FacilityRope1L();
};

