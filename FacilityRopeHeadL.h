#pragma once
#include "FacilityRopeHeadR.h"
class FacilityRopeHeadL :
    public FacilityRopeHeadR
{
public:
    static FacilityRopeHeadL* createNew();
    virtual void destroy();

protected:
    FacilityRopeHeadL();
    ~FacilityRopeHeadL();
};

