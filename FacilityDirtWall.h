#pragma once
#include "FacilityStatic.h"
class FacilityDirtWall :
    public FacilityStatic
{
public:
    static FacilityDirtWall* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityDirtWall();
    ~FacilityDirtWall();
};

