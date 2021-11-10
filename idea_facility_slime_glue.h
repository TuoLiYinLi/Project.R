#pragma once
#include "FacilityDynamic.h"
class idea_facility_slime_glue :
    public FacilityDynamic
{
public:
    static idea_facility_slime_glue* createNew();
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
    idea_facility_slime_glue();
    ~idea_facility_slime_glue();
};