#pragma once
#include "ImmediateProj.h"
class idea_projectile_slime_ball :
    public ImmediateProj
{
public:
    static idea_projectile_slime_ball* createNew();
    virtual void destroy();

    //����Ŀ���ɫ�ᴥ��
    virtual void onHit(Chara_old* c);
    //����Ŀ�꽨���ᴥ��
    virtual void onHit(Facility_old* f);
    //ʱ���������
    virtual void onEnd();

protected:
    idea_projectile_slime_ball();
    ~idea_projectile_slime_ball();
};

