#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_wall :
    public FacilityStatic
{
public:
    static idea_facility_dirt_wall* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    idea_facility_dirt_wall();
    ~idea_facility_dirt_wall();
};

