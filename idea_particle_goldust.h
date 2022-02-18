#pragma once
#include "Particle.h"
class idea_particle_goldust :
    public Particle
{
public:
    static idea_particle_goldust* createNew();
protected:
    idea_particle_goldust();
};

