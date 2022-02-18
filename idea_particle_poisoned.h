#pragma once
#include "Particle.h"
class idea_particle_poisoned :
    public Particle
{
public:
    static idea_particle_poisoned* createNew();
    void update() override;
protected:
    idea_particle_poisoned();
    double x_range;
    double t_phase;
};

