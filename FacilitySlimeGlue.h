#pragma once
#include "FacilityDynamic.h"
class FacilitySlimeGlue :
    public FacilityDynamic
{
public:
    static FacilitySlimeGlue* createNew();
    virtual void destroy();

	//�κ�ʱ�򴥷�
	virtual void onAnytime();
	//��������
	virtual void onActivate();
	//������
	virtual void onIdle();
	//����Ͷ�������
	virtual void onHit(Form* form);
	//������
	virtual void onDeath();


    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType();

protected:
    FacilitySlimeGlue();
    ~FacilitySlimeGlue();
};