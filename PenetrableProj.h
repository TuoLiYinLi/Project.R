#pragma once

#include "Projectile.h"

class PenetrableProj :
    public Projectile
{
public:
    static PenetrableProj* createNew();
    virtual void destroy();

    //����Ŀ���ɫ�ᴥ��
    virtual void onHit(Chara* c);
    //����Ŀ�꽨���ᴥ��
    virtual void onHit(Facility* f);
    //ʱ���������
    virtual void onEnd();
    //ÿ֡����
    void onFlying();
protected:
    PenetrableProj();
    ~PenetrableProj();
};

