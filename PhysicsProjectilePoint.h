#pragma once
#include "PhysicsProjectile.h"

//������ ����Ͷ����
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

    int x_aiming;  //Ŀ��λ��x
    int y_aiming;  //Ŀ��λ��y

    void setVelocity(double _v);//�����ٶ�
};

