#pragma once
#include "FacilityStatic.h"
class FacilityRope2R :
    public FacilityStatic
{
public:
    static FacilityRope2R* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityRope2R();
    ~FacilityRope2R();
};

