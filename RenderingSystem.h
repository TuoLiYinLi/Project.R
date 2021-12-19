#pragma once

#include <vector>
#include <list>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "AnimationUnit.h"
#include "EnumAnimationType.h"

class PhysicsObject;

class AnimationUnit;

class RenderingSystem
{
public:
	std::vector<std::vector<SDL_Texture*>*>* list_animation_texture;//һ����ά�Ĳ����б�,���ڼ������еĶ�����Դ
	std::list<AnimationUnit*>* list_animation_units;//������Ԫ�б�,������Ҫ��Ⱦ�Ķ���Ԫ��

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

	//��Ⱦ�����Ķ�����Ԫ
	void renderOneUnit(const AnimationUnit* au) const;
	//��Ⱦ���ж�����Ԫ(��������Ҫ��Ⱦ�Ĳ���)
	void renderAll() const;

	void renderTexture(SDL_Texture* texture, double x,double deltaX, double y, double deltaY, double w, double h,SDL_RendererFlip flip) const;

	void renderOnePhysicsObject(PhysicsObject* physics_object) const;

	//��Ⱦ���е�����ģ��
	void renderALLPhysicsObjects() const;

	//��Ⱦutf8���壬����bug����������������ʧ
	void renderText_UTF8( const char* utf8_msg,int x,int y) const;

	static  void getLengthUTF8(char const* str, int* cnt);//����str�й��ж����ַ��Լ����ж���1/2/3λ���ַ�(��4λ)

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
	
	//����ʵ��
	static RenderingSystem* instance;
	RenderingSystem();
	~RenderingSystem();


	TTF_Font* font_zpix;//ͨ�õ�ttf����
};

