#pragma once
#include "FacilityDynamic.h"
class idea_facility_slime_glue :
    public FacilityDynamic
{
public:
    static idea_facility_slime_glue* createNew();
    virtual void destroy();

	//任何时候触发
	virtual void onAnytime();
	//当被激活
	virtual void onActivate();
	//当闲置
	virtual void onIdle();
	//当被投射物击中
	virtual void onHit(Form* form);
	//当死亡
	virtual void onDeath();


    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();

protected:
    idea_facility_slime_glue();
    ~idea_facility_slime_glue();
};