#pragma once
#include "PhysicsProjectile.h"
class ProjectileFlying :
    public PhysicsProjectile
{
public:
    static ProjectileFlying* createNew();

	void update() override;

    double gravity; //����

    double x_a; //������ٶ�
    double y_a; //������ٶ�

    double damping;    //�ٶ�˥��ϵ��

protected:
    ProjectileFlying();
    ~ProjectileFlying()override;

};

