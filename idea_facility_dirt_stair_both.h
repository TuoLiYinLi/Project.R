#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_stair_both :
    public FacilityStatic
{
public:
    static idea_facility_dirt_stair_both* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    idea_facility_dirt_stair_both();
    ~idea_facility_dirt_stair_both();
};

