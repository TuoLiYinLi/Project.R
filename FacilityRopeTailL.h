#pragma once
#include "FacilityRopeTailR.h"
class FacilityRopeTailL :
    public FacilityRopeTailR
{
public:
    static FacilityRopeTailL* createNew();
    virtual void destroy();

protected:
    FacilityRopeTailL();
};

