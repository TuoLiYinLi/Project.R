#pragma once
#include "FacilityDynamic.h"
class idea_facility_dirt_cracked :
    public FacilityDynamic
{
public:
    static idea_facility_dirt_cracked* createNew();
    virtual void destroy();
    //����Ͷ�������
    virtual void onHit(Form* form);

	//��ȡ��ǰ������Ӧ�Ķ�������
	virtual AnimType getAnimType();
protected:
    idea_facility_dirt_cracked();
    ~idea_facility_dirt_cracked();
};

