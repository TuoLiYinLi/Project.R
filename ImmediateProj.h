#pragma once
#include "Projectile.h"
class ImmediateProj :
    public Projectile
{
public:
    static ImmediateProj* createNew();
    virtual void destroy();

    //碰到目标角色会触发
    virtual void onHit(Chara_old* c);
    //碰到目标建筑会触发
    virtual void onHit(Facility_old* f);
    //时间结束触发
    virtual void onEnd();
    //每帧触发
    void onFlying();
protected:
    ImmediateProj();
    ~ImmediateProj();

};

