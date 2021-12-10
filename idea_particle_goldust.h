#pragma once
#include "AnimParticle.h"
#include "AnimationSystem.h"
class idea_particle_goldust :
    public AnimParticle
{
public:
    static idea_particle_goldust* createNew();
    void destroy();
protected:
    idea_particle_goldust();
    ~idea_particle_goldust();
};

