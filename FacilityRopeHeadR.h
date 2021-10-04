#pragma once
#include "FacilityStatic.h"
class FacilityRopeHeadR :
    public FacilityStatic
{
public:
    static FacilityRopeHeadR* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityRopeHeadR();
    ~FacilityRopeHeadR();
    };

