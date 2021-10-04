#pragma once
#include "FacilityStatic.h"
class FacilityRopeTailR :
    public FacilityStatic
{
public:
    static FacilityRopeTailR* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityRopeTailR();
    ~FacilityRopeTailR();
};

