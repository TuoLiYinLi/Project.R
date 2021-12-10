#pragma once
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "AnimType.h"

#include "AnimationSystem.h"
class AnimationSystem;

class AnimationUnit
{
public:
	unsigned short depth;//�������Ԫ�������,����Ⱦʱ������Ⱦ��С��ȵ�ͼ��

	AnimType type;//�������Ԫ��������,˵������ʲô����
	int animProgress;//��ʾ��Ⱦ��������ĵڼ�֡

	double deltaX;//��Ⱦʱ��ƫ��λ��Y,��1/16������Ϊ��λ
	double deltaY;//��Ⱦʱ��ƫ��λ��Y,��1/16������Ϊ��λ

	double x;//��Ⱦ����������λ��
	double y;//��Ⱦ����������λ��

	double width;//Ԫ����ʾ�Ŀ��
	double height;//Ԫ����ʾ�ĸ߶�

	double angle;//Ԫ�������ĵ���ת�ĽǶ�,�Ƕ��ƶ�
	SDL_RendererFlip flip;//�Ƿ����ת,һ�㲻��תʱ,��ɫ�泯�ұ�

	//���ö���Ԫ������ʾλ�ú�״̬
	AnimationUnit* set(double _x,double _y,double _width=-1,double _height=-1,double _angle=0);

	//�����µĶ���Ԫ��
	static AnimationUnit* createNew();
	//�������Ԫ��
	void destroy();
	//��ȡ����ʹ���ڴ�Ķ���Ԫ������
	static int getCurrentNum();

protected:
	static int currentNum;//��¼һ���ж��ٵĶ���Ԫ��ռ���ڴ�
	AnimationUnit();
	~AnimationUnit();
};

