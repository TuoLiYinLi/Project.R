#pragma once
#include "Projectile.h"
class ImmediateProj :
    public Projectile
{
public:
    static ImmediateProj* createNew();
    virtual void destroy();

    //����Ŀ���ɫ�ᴥ��
    virtual void onHit(Chara_old* c);
    //����Ŀ�꽨���ᴥ��
    virtual void onHit(Facility_old* f);
    //ʱ���������
    virtual void onEnd();
    //ÿ֡����
    void onFlying();
protected:
    ImmediateProj();
    ~ImmediateProj();

};

