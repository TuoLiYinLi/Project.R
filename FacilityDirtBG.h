#pragma once
#include "FacilityStatic.h"
class FacilityDirtBG :
    public FacilityStatic
{
public:
    //�����µ�
    static FacilityDirtBG* createNew();
    //����
    virtual void destroy();

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilityDirtBG();
    ~FacilityDirtBG();
};

