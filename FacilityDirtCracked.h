#pragma once
#include "FacilityDynamic.h"
class FacilityDirtCracked :
    public FacilityDynamic
{
public:
    static FacilityDirtCracked* createNew();
    virtual void destroy();
    //����Ͷ�������
    virtual void onHit(Form* form);

	//��ȡ��ǰ������Ӧ�Ķ�������
	virtual AnimType getAnimType();
protected:
    FacilityDirtCracked();
    ~FacilityDirtCracked();
};

