#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_stair_right :
    public FacilityStatic
{
public:
    static idea_facility_dirt_stair_right* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    idea_facility_dirt_stair_right();
    ~idea_facility_dirt_stair_right();
};

