#pragma once
#include <SDL.h>
#include "PhysicsObject.h"

class GameToolkit
{
public:
	//����������ת��Ϊ��������
	static void transPositionWorldToWindow(double x_world,double y_world,double* x_window,double* y_window);
	//����������ת��Ϊ��������
	static void transPositionWindowToWorld(double x_window, double y_window, double* x_world, double* y_world);

	//����һ���ض���ɫ��͸������,����ָ�봫�ݳ����ɵĿ�Ⱥ͸߶�
	static SDL_Texture* getRenderedText(char const*utf8_str, SDL_Color color,int* width,int* height);

	//���������Ӫ�Ƿ�ս(��ƽ��Ӫ��Զ���ж�,ͬ��ӪҲ���ж�)
	static bool checkIfHostile(AllyType _t1, AllyType _t2);

	//����t�����˵�CD
	static int getWaveTime(int t);

	//�������Ƿ���ĳ���η�Χ��
	static bool checkMouseInRange(int _x1, int _y1, int _x2, int _y2);
};

