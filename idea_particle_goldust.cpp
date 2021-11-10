#include "idea_particle_goldust.h"

idea_particle_goldust* idea_particle_goldust::createNew()
{
    auto p = new idea_particle_goldust();
#ifdef _DEBUG
    if (p == nullptr) {
        std::cout << "\t\tParticleGoldust::createNew()ÄÚ´æ²»×ã\n";
    }
#endif // _DEBUG
    return p;
}

void idea_particle_goldust::destroy()
{
    delete this;
}

idea_particle_goldust::idea_particle_goldust()
{
    animUnit = AnimationUnit::createNew();
    animUnit->type = AnimType::particle_goldust;
    animUnit->depth = 300;

    w = 16;
    h = 16;

    animCycle = 40;
    animProgress = rand() % 40;
    livingTime = animCycle-animProgress;
    v_angle = double(rand() % 10) / 100;
    scale = double(rand() % 30) / 100 + 0.6;
    v_x = double(rand() % 11 - 5) / 100;
    a_x = -v_x / livingTime;
    v_y = double(rand() % 11 - 5) / 100;
    a_y = -v_y / livingTime;

}

idea_particle_goldust::~idea_particle_goldust()
{
}
