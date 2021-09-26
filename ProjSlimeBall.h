#pragma once
#include "ImmediateProj.h"
class ProjSlimeBall :
    public ImmediateProj
{
public:
    static ProjSlimeBall* createNew();
    virtual void destroy();

    //碰到目标角色会触发
    virtual void onHit(Chara* c);
    //碰到目标建筑会触发
    virtual void onHit(Facility* f);
    //时间结束触发
    virtual void onEnd();

protected:
    ProjSlimeBall();
    ~ProjSlimeBall();
};

