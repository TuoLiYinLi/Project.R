#pragma once
#include "GameObject.h"

//游戏物体 单个粒子
class Particle :
    public GameObject
{
public:
    static Particle* createNew();

protected:
    Particle();
    ~Particle()override;
};

