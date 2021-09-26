#pragma once
#include "FacilityDynamic.h"
class FacilityDirtCracked :
    public FacilityDynamic
{
public:
    static FacilityDirtCracked* createNew();
    virtual void destroy();
    //当被投射物击中
    virtual void onHit(Form* form);

	//获取当前动作对应的动画种类
	virtual AnimType getAnimType();
protected:
    FacilityDirtCracked();
    ~FacilityDirtCracked();
};

