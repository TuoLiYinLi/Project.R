#pragma once
#include "FacilityStatic.h"
class FacilityRopeTailR :
    public FacilityStatic
{
public:
    static FacilityRopeTailR* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityRopeTailR();
    ~FacilityRopeTailR();
};

