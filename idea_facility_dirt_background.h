#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_background :
    public FacilityStatic
{
public:
    //创建新的
    static idea_facility_dirt_background* createNew();
    //销毁
    virtual void destroy() override;

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType() override;

protected:
    idea_facility_dirt_background();
    ~idea_facility_dirt_background();
};

