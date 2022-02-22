#pragma once
#include "Particle.h"
class idea_particle_healing :
    public Particle
{
public:
    static idea_particle_healing* createNew();

protected:
    idea_particle_healing();
};

