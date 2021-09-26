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
	std::list<TTFParticle*>* ttfParticleList;//���������б�
	std::list<AnimParticle*>* animParticleList;//���������б�

	//����ttf����
	//TTFParticle* addTTFParticle();
	//������������
	//AnimParticle* addAnimParticle(AnimParticle* ap);
	//�Ƴ�����
	void removeParticle(TTFParticle* ttfParticle);
	//�Ƴ�����
	void removeParticle(AnimParticle* animParticle);
	//�õ������Ƴ�����
	std::list<TTFParticle*>::iterator removeParticleIt(std::list<TTFParticle*>::iterator it);
	//�õ������Ƴ�����
	std::list<AnimParticle*>::iterator removeParticleIt(std::list<AnimParticle*>::iterator it);


	//��ȡ����ʵ��
	static ParticleSystem* getInstance();
	//�ݻ�ʵ��
	void destroyInstance();

protected:
	static ParticleSystem* instance;
	ParticleSystem();
	~ParticleSystem();
};

