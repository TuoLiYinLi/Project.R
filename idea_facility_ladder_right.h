#pragma once
#include "idea_facility_ladder_left.h"
class idea_facility_ladder_right :
    public idea_facility_ladder_left
{
public:
    static idea_facility_ladder_right* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();
protected:
    idea_facility_ladder_right();
    ~idea_facility_ladder_right();
};

