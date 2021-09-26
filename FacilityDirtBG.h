#pragma once
#include "FacilityStatic.h"
class FacilityDirtBG :
    public FacilityStatic
{
public:
    //创建新的
    static FacilityDirtBG* createNew();
    //销毁
    virtual void destroy();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    FacilityDirtBG();
    ~FacilityDirtBG();
};

