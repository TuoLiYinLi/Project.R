#pragma once
#include "FacilityStatic.h"
class idea_facility_ladder_left :
    public FacilityStatic
{
public:
    static idea_facility_ladder_left* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    idea_facility_ladder_left();
    ~idea_facility_ladder_left();
};

