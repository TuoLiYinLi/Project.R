#pragma once
#include "FacilityStatic.h"
class FacilityRopeHeadR :
    public FacilityStatic
{
public:
    static FacilityRopeHeadR* createNew();
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityRopeHeadR();
    ~FacilityRopeHeadR();
    };

