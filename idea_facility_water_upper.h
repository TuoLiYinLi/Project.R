#pragma once
#include "FacilityDynamic.h"
class idea_facility_water_upper :
    public FacilityDynamic
{
public:
    static idea_facility_water_upper* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();
protected:
    idea_facility_water_upper();
    ~idea_facility_water_upper();
};

