#pragma once
#include "FacilityStatic.h"
class FacilityDirtStairL :
    public FacilityStatic
{
public:
    static FacilityDirtStairL* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityDirtStairL();
    ~FacilityDirtStairL();
};

