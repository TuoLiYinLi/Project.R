#pragma once
#include "FacilityDynamic.h"
class idea_facility_water_full :
    public FacilityDynamic
{
public:
    static idea_facility_water_full* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();
protected:
    idea_facility_water_full();
    ~idea_facility_water_full();
};

