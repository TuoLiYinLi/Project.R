#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_stair_left :
    public FacilityStatic
{
public:
    static idea_facility_dirt_stair_left* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    idea_facility_dirt_stair_left();
    ~idea_facility_dirt_stair_left();
};

