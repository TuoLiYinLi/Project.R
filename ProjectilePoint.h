#pragma once
#include "PhysicsProjectile.h"
class ProjectilePoint :
    public PhysicsProjectile
{
public:
    static ProjectilePoint* createNew();

	void update() override;

    void setAiming(int _x, int _y);

protected:
    ProjectilePoint();
    ~ProjectilePoint() override;

    int x_aiming;  //目标位置x
    int y_aiming;  //目标位置y

    void setVelocity(double _v);//设置速度
};

