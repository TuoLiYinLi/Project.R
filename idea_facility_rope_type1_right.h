#pragma once
#include "FacilityStatic.h"
class idea_facility_rope_type1_right :
    public FacilityStatic
{
public:
    static idea_facility_rope_type1_right* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    idea_facility_rope_type1_right();
    ~idea_facility_rope_type1_right();
};
