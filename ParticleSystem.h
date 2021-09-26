#pragma once
#include <list>

#include "TTFParticle.h"
class TTFParticle;
#include "AnimParticle.h"
class AnimParticle;
#include "AnimSystem.h"
class ParticleSystem
{
public:
	std::list<TTFParticle*>* ttfParticleList;//文字粒子列表
	std::list<AnimParticle*>* animParticleList;//动画粒子列表

	//新增ttf粒子
	//TTFParticle* addTTFParticle();
	//新增动画粒子
	//AnimParticle* addAnimParticle(AnimParticle* ap);
	//移除粒子
	void removeParticle(TTFParticle* ttfParticle);
	//移除粒子
	void removeParticle(AnimParticle* animParticle);
	//用迭代器移除粒子
	std::list<TTFParticle*>::iterator removeParticleIt(std::list<TTFParticle*>::iterator it);
	//用迭代器移除粒子
	std::list<AnimParticle*>::iterator removeParticleIt(std::list<AnimParticle*>::iterator it);


	//获取单例实例
	static ParticleSystem* getInstance();
	//摧毁实例
	void destroyInstance();

protected:
	static ParticleSystem* instance;
	ParticleSystem();
	~ParticleSystem();
};

