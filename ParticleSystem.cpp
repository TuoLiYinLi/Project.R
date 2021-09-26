#include "ParticleSystem.h"
#include "Defined.h"

ParticleSystem* ParticleSystem::instance = nullptr;
/*
TTFParticle* ParticleSystem::addTTFParticle()
{
	TTFParticle* tp = TTFParticle::createNew();
	this->ttfParticleList->push_back(tp);
	return tp;
}

AnimParticle* ParticleSystem::addAnimParticle(AnimParticle* ap)
{
	this->animParticleList->push_back(ap);
	return ap;
}
*/

void ParticleSystem::removeParticle(TTFParticle* ttfParticle)
{
	ttfParticleList->remove(ttfParticle);
	if (ttfParticle->fontUnit != nullptr) {
		AnimSystem::getInstance()->removeTTFUnit(ttfParticle->fontUnit);
		ttfParticle->fontUnit = nullptr;
	}
	ttfParticle->destroy();
}

void ParticleSystem::removeParticle(AnimParticle* animParticle)
{
	animParticleList->remove(animParticle);
	if (animParticle->animUnit != nullptr) {
		AnimSystem::getInstance()->removeAnimUnit(animParticle->animUnit);
		animParticle->animUnit = nullptr;
	}
	animParticle->destroy();
}

std::list<TTFParticle*>::iterator ParticleSystem::removeParticleIt(std::list<TTFParticle*>::iterator it)
{
	if ((*it)->fontUnit != nullptr) {
		AnimSystem::getInstance()->removeTTFUnit((*it)->fontUnit);
		(*it)->fontUnit = nullptr;
	}
	(*it)->destroy();
	auto r= ttfParticleList->erase(it);
	return r;
}

std::list<AnimParticle*>::iterator ParticleSystem::removeParticleIt(std::list<AnimParticle*>::iterator it)
{
	if ((*it)->animUnit != nullptr) {
		AnimSystem::getInstance()->removeAnimUnit((*it)->animUnit);
		(*it)->animUnit = nullptr;
	}
	auto r = animParticleList->erase(it);
	(*it)->destroy();
	return r;
}

ParticleSystem* ParticleSystem::getInstance()
{
	if (instance == nullptr) {
		instance = new ParticleSystem();
	}
	return instance;
}

void ParticleSystem::destroyInstance()
{

	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

ParticleSystem::ParticleSystem()
{
#ifdef PARTICLE_SYSTEM_DEBUG
	std::cout << "ParticleSystem::ParticleSystem()\n";
#endif // PARTICLE_SYSTEM_DEBUG
	ttfParticleList = new std::list<TTFParticle*>();
	animParticleList = new std::list<AnimParticle*>();
}

ParticleSystem::~ParticleSystem()
{
#ifdef PARTICLE_SYSTEM_DEBUG
	std::cout << "ParticleSystem::~ParticleSystem()\n";
#endif // PARTICLE_SYSTEM_DEBUG
	auto it = ttfParticleList->begin();
	while (true)
	{
		if (it != ttfParticleList->end()) 
		{
			it = removeParticleIt(it);
		}
		else
		{
			break;
		}
	}
}


