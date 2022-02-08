#pragma once

#include <vector>
#include <list>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "RenderingUnit.h"
#include "EnumAnimationType.h"

class PhysicsObject;

class RenderingAnimation;

class RenderingSystem
{


public:
	TTF_Font* font_grey;//����Silver.ttf

	//��ȡ����ʵ��
	static RenderingSystem* getInstance();

	//���ٺ�����
	static void destroyInstance();

	void add(RenderingUnit* ru)const;

	void remove(RenderingUnit* ru)const;

	//����ĳһ�ֶ�����Դ
	void loadAnimation( AnimationType antp)const;
	//������������Ķ�����Դ
	void loadAllAnimation()const;
	//ж��ĳһ�ֶ�����Դ
	void unloadAnimation(AnimationType antp) const;
	//ж����������Ķ�����Դ
	void unloadAllAnimation()const;

	//�������ʼ��

	//��Ⱦ��������Ⱦ��Ԫ
	void renderOneUnit(const RenderingUnit* au) const;

	//��RenderingUnits��������
	void sortRenderingUnits() const;

	//��Ⱦ���ж�����Ԫ(��������Ҫ��Ⱦ�Ĳ���)
	void renderAll() const;
	
	SDL_Texture* getAnimation(AnimationType _animation_type,unsigned long long num)const;
	unsigned long long getAnimationSize(AnimationType _animation_type)const;

	//�ı��ӿ�λ��
	void renewViewPosition();

	double window_width;//���ڿ��
	double window_height;//���ڸ߶�

	double vy;//���ڵ�Y����ı��ٶ�
	double vx;//���ڵ�X����ı��ٶ�
	double vs;//���ڵ�����ˮƽ�ı��ٶ�

	double viewX;//���ڵ�X��������
	double viewY;//���ڵ�Y��������
	double viewScale;//���ڵ�����ˮƽ

protected:
	RenderingSystem();
	~RenderingSystem();

	static RenderingSystem* instance;//����ʵ��

	std::list<RenderingUnit*>* list_rendering_units;//������Ԫ�б�,������Ҫ��Ⱦ�Ķ���Ԫ��
	std::vector<std::vector<SDL_Texture*>*>* list_animation_texture;//һ����ά�Ĳ����б�,���ڼ������еĶ�����Դ

	static bool compareDepth(const RenderingUnit* ru1, const RenderingUnit* ru2);//�Ƚ�������Ⱦ��Ԫ�Ĵ�С,��������ص�����
};

