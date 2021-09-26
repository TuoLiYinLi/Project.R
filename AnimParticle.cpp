#include "AnimParticle.h"

AnimParticle* AnimParticle::createNew()
{
    auto ap = new AnimParticle();
#ifdef _DEBUG
    if (ap == nullptr) {
        std::cout << "\t\tAnimParticle::createNew()ÄÚ´æ²»×ã\n";
    }
#endif // _DEBUG
    return ap;
}

void AnimParticle::destroy()
{
    delete this;
}

AnimParticle::AnimParticle()
{
    ParticleSystem::getInstance()->animParticleList->push_back(this);

    animUnit = nullptr;
    animCycle = 0;
    animProgress = 0;
    livingTime = 0;
    x = 0;
    y = 0;
    w = 16;
    h = 16;
    angle = 0;
    scale = 0;

    v_x = 0;
    v_y = 0;
    v_angle = 0;
    v_scale = 0;

    a_x = 0;
    a_y = 0;
    a_angle = 0;
    a_scale = 0;
}

AnimParticle::~AnimParticle()
{
}
