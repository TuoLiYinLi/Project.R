#pragma once
#include "FacilityStatic.h"
class FacilityLadderL :
    public FacilityStatic
{
public:
    static FacilityLadderL* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityLadderL();
    ~FacilityLadderL();
};

