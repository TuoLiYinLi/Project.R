#pragma once

#include "SDL.h"
#include "EnumAnimationType.h"

class GameObject;
class RenderingSystem;

class AnimationUnit
{
public:
	//�����µĶ���Ԫ��
	static AnimationUnit* createNew();
	//�������Ԫ��
	void destroy() const;

	unsigned short depth;//�������Ԫ�������,����Ⱦʱ������Ⱦ��С��ȵ�ͼ��

	double deltaX;//��Ⱦʱ��ƫ��λ��Y,��1/16������Ϊ��λ
	double deltaY;//��Ⱦʱ��ƫ��λ��Y,��1/16������Ϊ��λ

	double x;//��Ⱦ����������λ��
	double y;//��Ⱦ����������λ��

	double width;//Ԫ����ʾ�Ŀ��
	double height;//Ԫ����ʾ�ĸ߶�
	
	void setFlip(bool _val);	//�����Ƿ�ת
	SDL_RendererFlip getFlip() const;	//ȡ���Ƿ�ת

	void setTexture(AnimationType type, int time_length, int current);
	SDL_Texture* getTexture() const; //ȡ�ö�Ӧ����

	static int getCurrentNum();	//��ȡ����ʹ���ڴ�Ķ���Ԫ������

protected:
	static int current_num;//��¼һ���ж��ٵĶ���Ԫ��ռ���ڴ�

	AnimationUnit();
	~AnimationUnit();

	bool flip;//�Ƿ����ת,һ�㲻��תʱ,��ɫ�泯�ұ�

	SDL_Texture* texture;//���еĲ���
};

