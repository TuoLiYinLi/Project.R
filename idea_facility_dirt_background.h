#pragma once
#include "FacilityStatic.h"
class idea_facility_dirt_background :
    public FacilityStatic
{
public:
    //�����µ�
    static idea_facility_dirt_background* createNew();
    //����
    virtual void destroy() override;

    //��ȡ��ǰ������Ӧ�Ķ�������
    virtual AnimType getAnimType() override;

protected:
    idea_facility_dirt_background();
    ~idea_facility_dirt_background();
};

