#pragma once
#include "FacilityStatic.h"
class FacilityDirtStairR :
    public FacilityStatic
{
public:
    static FacilityDirtStairR* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityDirtStairR();
    ~FacilityDirtStairR();
};

