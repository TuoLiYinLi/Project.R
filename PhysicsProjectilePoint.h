#pragma once
#include "PhysicsProjectile.h"

//物理体 定点投射物
class PhysicsProjectilePoint :
    public PhysicsProjectile
{
public:
    static PhysicsProjectilePoint* createNew();

	void update() override;

    void setup(int _x, int _y, double _velocity);

protected:
    PhysicsProjectilePoint();
    ~PhysicsProjectilePoint() override;

    int x_aiming;  //目标位置x
    int y_aiming;  //目标位置y

    void setVelocity(double _v);//设置速度
};

