#pragma once
#include "FacilityStatic.h"
class FacilityDirtStairB :
    public FacilityStatic
{
public:
    static FacilityDirtStairB* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityDirtStairB();
    ~FacilityDirtStairB();
};

