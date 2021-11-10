#pragma once
#include "PenetrableProj.h"

class idea_projectile_chop :
    public PenetrableProj
{
public:
    static idea_projectile_chop* createNew();
    virtual void destroy();

    //碰到目标角色会触发
    virtual void onHit(Chara* c);
    //碰到目标建筑会触发
    virtual void onHit(Facility* f);
protected:
    std::list<Chara*>* hitCharaList;//已经击中过的角色
    std::list<Facility*>* hitFaciList;//已经击中过的设施
    idea_projectile_chop();
    ~idea_projectile_chop();
};

