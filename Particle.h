#pragma once
#include "GameObject.h"

//��Ϸ���� ��������
class Particle :
    public GameObject
{
public:
    static Particle* createNew();

protected:
    Particle();
    ~Particle()override;
};

