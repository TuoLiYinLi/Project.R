#pragma once
#include "FacilityLadderL.h"
class FacilityLadderR :
    public FacilityLadderL
{
public:
    static FacilityLadderR* createNew();
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();
protected:
    FacilityLadderR();
    ~FacilityLadderR();
};

