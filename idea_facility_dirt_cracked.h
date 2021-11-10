#pragma once
#include "FacilityDynamic.h"
class idea_facility_dirt_cracked :
    public FacilityDynamic
{
public:
    static idea_facility_dirt_cracked* createNew();
    virtual void destroy();
    //当被投射物击中
    virtual void onHit(Form* form);

	//获取当前动作对应的动画种类
	virtual AnimType getAnimType();
protected:
    idea_facility_dirt_cracked();
    ~idea_facility_dirt_cracked();
};

