#pragma once
#include "FacilityDynamic.h"
class FacilityWaterUpper :
    public FacilityDynamic
{
public:
    static FacilityWaterUpper* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();
protected:
    FacilityWaterUpper();
    ~FacilityWaterUpper();
};

