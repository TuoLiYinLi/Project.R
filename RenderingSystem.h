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
	std::vector<std::vector<SDL_Texture*>*>* list_animation_texture;//һ����ά�Ĳ����б�,���ڼ������еĶ�����Դ
	std::list<RenderingUnit*>* list_rendering_units;//������Ԫ�б�,������Ҫ��Ⱦ�Ķ���Ԫ��

	TTF_Font* font_zpix;//ͨ�õ�ttf����

	//��ȡ����ʵ��
	static RenderingSystem* getInstance();

	//���ٺ�����
	static void destroyInstance();

	//����ĳһ�ֶ�����Դ
	void loadAnim( AnimationType antp);
	//������������Ķ�����Դ
	void loadAllAnim();
	//ж��ĳһ�ֶ�����Դ
	void unloadAnim(AnimationType antp) const;
	//ж����������Ķ�����Դ
	void unloadAllAnim();

	//��Ⱦ��������Ⱦ��Ԫ
	void renderOneUnit(const RenderingUnit* au) const;

	//��RenderingUnits��������
	void sortRenderingUnits() const;

	//��Ⱦ���ж�����Ԫ(��������Ҫ��Ⱦ�Ĳ���)
	void renderAll() const;

	void renderTexture(SDL_Texture* texture, double x,double deltaX, double y, double deltaY, double w, double h,SDL_RendererFlip flip) const;

	void renderOnePhysicsObject(PhysicsObject* physics_object) const;

	//��Ⱦ���е�����ģ��
	void renderALLPhysicsObjects() const;
	

	static void getLengthUTF8(char const* str, int* cnt);//����str�й��ж����ַ��Լ����ж���1/2/3λ���ַ�(��4λ)

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

	static RenderingSystem* instance;//����ʵ��
	RenderingSystem();
	~RenderingSystem();


};

