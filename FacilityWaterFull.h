#pragma once
#include "FacilityDynamic.h"
class FacilityWaterFull :
    public FacilityDynamic
{
public:
    static FacilityWaterFull* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();
protected:
    FacilityWaterFull();
    ~FacilityWaterFull();
};

