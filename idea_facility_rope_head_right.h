#pragma once
#include "FacilityStatic.h"
class idea_facility_rope_head_right :
    public FacilityStatic
{
public:
    static idea_facility_rope_head_right* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    idea_facility_rope_head_right();
    ~idea_facility_rope_head_right();
    };

