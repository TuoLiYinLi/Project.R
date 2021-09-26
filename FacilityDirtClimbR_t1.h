#pragma once
#include "FacilityDirtClimbL_t1.h"
class FacilityDirtClimbR_t1 :
    public FacilityDirtClimbL_t1
{
public:
    static FacilityDirtClimbR_t1* createNew();
    virtual void destroy();

protected:
    FacilityDirtClimbR_t1();
};

