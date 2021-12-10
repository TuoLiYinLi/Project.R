#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//#include "GlobalData.h"

#include "AnimationSystem.h"
class AnimationSystem;

class TTFUnit
{
public:
	SDL_Color color;//��ɫ��Ϣ
	double world_x;//��������_X
	double world_y;//��������_Y
	double scale;//����ϵ��
	unsigned short depth;
	int w;
	int h;
	
	SDL_Texture* texture;//����������

	//������ʾλ��
	void set(double x,double y);

	static TTFUnit* createNew(const char* _message, SDL_Color _color);
	void destroy();

	//��ȡ��ǰ����ռ���ڴ�����ֵ�Ԫ����
	static int getCurrentNum();
protected:
	static int currentNum;//��¼һ���ж��ٵ�����Ԫ��ռ���ڴ�
	TTFUnit(const char* _message, SDL_Color _color);
	~TTFUnit();
};

