#include "TTFParticle.h"

TTFParticle* TTFParticle::createNew()
{
	auto tp = new TTFParticle();
#ifdef _DEBUG
	if (tp == nullptr) {
		std::cout << "\t\tTTFParticle::createNew()ÄÚ´æ²»×ã\n";
	}
#endif // _DEBUG
	return tp;
}

void TTFParticle::destroy()
{
	delete this;
}

TTFParticle::TTFParticle()
{
	ParticleSystem::getInstance()->ttfParticleList->push_back(this);

	fontUnit = nullptr;
	
	livingTime = 0;

	x = 0;
	y = 0;
	scale = 1;

	v_x = 0;
	v_y = 0;
	v_scale = 0;

	a_x = 0;
	a_y = 0;
	a_scale = 0;
}

TTFParticle::~TTFParticle()
{
}
