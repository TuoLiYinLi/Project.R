#pragma once
#include "Particle.h"
class idea_particle_flame :
    public Particle
{
public:
    static idea_particle_flame* createNew();
	void update() override;
protected:
    idea_particle_flame();
};

