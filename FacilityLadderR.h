#pragma once
#include "FacilityLadderL.h"
class FacilityLadderR :
    public FacilityLadderL
{
public:
    static FacilityLadderR* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();
protected:
    FacilityLadderR();
    ~FacilityLadderR();
};

