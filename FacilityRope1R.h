#pragma once
#include "FacilityStatic.h"
class FacilityRope1R :
    public FacilityStatic
{
public:
    static FacilityRope1R* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityRope1R();
    ~FacilityRope1R();
};

