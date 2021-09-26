#pragma once

#include "Projectile.h"

class PenetrableProj :
    public Projectile
{
public:
    static PenetrableProj* createNew();
    virtual void destroy();

    //碰到目标角色会触发
    virtual void onHit(Chara* c);
    //碰到目标建筑会触发
    virtual void onHit(Facility* f);
    //时间结束触发
    virtual void onEnd();
    //每帧触发
    void onFlying();
protected:
    PenetrableProj();
    ~PenetrableProj();
};

