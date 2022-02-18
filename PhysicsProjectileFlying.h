#pragma once
#include "PhysicsProjectile.h"
#include "integration_recorder.h"

//物理体 飞行投射物
class PhysicsProjectileFlying :
    public PhysicsProjectile
{
public:
    static PhysicsProjectileFlying* createNew();

	void update() override;

    void setup(double _x_a, double _y_a, double _gravity, double _damping);

protected:
    PhysicsProjectileFlying();
    ~PhysicsProjectileFlying()override;

    double gravity; //重力

    double x_a; //纵向加速度
    double y_a; //横向加速度

    double damping;    //速度衰减系数
};

