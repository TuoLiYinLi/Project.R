#pragma once
#include "PhysicsProjectile.h"
#include "integration_recorder.h"

//������ ����Ͷ����
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

    double gravity; //����

    double x_a; //������ٶ�
    double y_a; //������ٶ�

    double damping;    //�ٶ�˥��ϵ��
};

