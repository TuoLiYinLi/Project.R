#pragma once

#include <vector>
#include <list>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "RenderingAnimation.h"
#include "RenderingUnit.h"
#include "EnumAnimationType.h"

class PhysicsObject;

class RenderingAnimation;

class RenderingSystem
{


public:
	TTF_Font* font_zpix;//ͨ�õ�ttf����

	//��ȡ����ʵ��
	static RenderingSystem* getInstance();

	//���ٺ�����
	static void destroyInstance();

	void add(RenderingUnit* ru)const;

	void remove(RenderingUnit* ru)const;

	//����ĳһ�ֶ�����Դ
	void loadAnimation( AnimationType antp);
	//������������Ķ�����Դ
	void loadAllAnimation();
	//ж��ĳһ�ֶ�����Դ
	void unloadAnimation(AnimationType antp) const;
	//ж����������Ķ�����Դ
	void unloadAllAnimation();

	//��Ⱦ��������Ⱦ��Ԫ
	void renderOneUnit(const RenderingUnit* au) const;

	//��RenderingUnits��������
	void sortRenderingUnits() const;

	//��Ⱦ���ж�����Ԫ(��������Ҫ��Ⱦ�Ĳ���)
	void renderAll() const;

	void renderTexture(SDL_Texture* texture, double x,double deltaX, double y, double deltaY, double w, double h,SDL_RendererFlip flip) const;
	
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
	std::list<RenderingUnit*>* list_rendering_units;//������Ԫ�б�,������Ҫ��Ⱦ�Ķ���Ԫ��
	std::vector<std::vector<SDL_Texture*>*>* list_animation_texture;//һ����ά�Ĳ����б�,���ڼ������еĶ�����Դ

	static RenderingSystem* instance;//����ʵ��
	RenderingSystem();
	~RenderingSystem();

	static bool compareDepth(RenderingUnit* ru1, RenderingUnit* ru2);
};

