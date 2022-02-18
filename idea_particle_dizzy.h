#pragma once
#include "Particle.h"
class idea_particle_dizzy :
    public Particle
{
public:
    static idea_particle_dizzy* createNew();
    void update() override;
protected:
    idea_particle_dizzy();
};

