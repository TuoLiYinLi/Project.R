#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_climb_type1_left :
    public FacilityStatic
{
public:
    static idea_facility_dirt_climb_type1_left* createNew();
    virtual void destroy() override;

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType()override;
protected:
    idea_facility_dirt_climb_type1_left();
    ~idea_facility_dirt_climb_type1_left();
};

