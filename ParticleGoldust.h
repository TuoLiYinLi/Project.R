#pragma once
#include "AnimParticle.h"
#include "AnimSystem.h"
class ParticleGoldust :
    public AnimParticle
{
public:
    static ParticleGoldust* createNew();
    void destroy();
protected:
    ParticleGoldust();
    ~ParticleGoldust();
};

