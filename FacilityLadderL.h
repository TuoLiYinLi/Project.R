#pragma once
#include "FacilityStatic.h"
class FacilityLadderL :
    public FacilityStatic
{
public:
    static FacilityLadderL* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityLadderL();
    ~FacilityLadderL();
};

