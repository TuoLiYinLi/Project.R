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

    int x_aiming;  //Ŀ��λ��x
    int y_aiming;  //Ŀ��λ��y

    void setVelocity(double _v);//�����ٶ�
};

