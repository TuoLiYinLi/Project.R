#pragma once
#include "ImmediateProj.h"
class idea_projectile_slime_ball :
    public ImmediateProj
{
public:
    static idea_projectile_slime_ball* createNew();
    virtual void destroy();

    //碰到目标角色会触发
    virtual void onHit(Chara* c);
    //碰到目标建筑会触发
    virtual void onHit(Facility* f);
    //时间结束触发
    virtual void onEnd();

protected:
    idea_projectile_slime_ball();
    ~idea_projectile_slime_ball();
};

