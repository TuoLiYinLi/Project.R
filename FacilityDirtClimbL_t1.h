#pragma once
#include "FacilityStatic.h"
class FacilityDirtClimbL_t1 :
    public FacilityStatic
{
public:
    static FacilityDirtClimbL_t1* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();
protected:
    FacilityDirtClimbL_t1();
    ~FacilityDirtClimbL_t1();
};

