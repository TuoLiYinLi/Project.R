#pragma once
#include <SDL.h>
#include "PhysicsObject.h"

class GameToolkit
{
public:
	//将世界坐标转换为窗口坐标
	static void transPositionWorldToWindow(double x_world,double y_world,double* x_window,double* y_window);
	//将窗口坐标转换为世界坐标
	static void transPositionWindowToWorld(double x_window, double y_window, double* x_world, double* y_world);

	//计算str中共有多少字符以及含有多少1/2/3位的字符(共4位)
	static void getLengthUTF8(char const* str, int* cnt);

	//生成一个特定颜色的透明字体,并用指针传递出生成的宽度和高度
	static SDL_Texture* getRenderedText(char const*utf8_str, SDL_Color color,int* width,int* height);

	//检查两个阵营是否交战(和平阵营永远不敌对,同阵营也不敌对)
	static bool checkIfHostile(AllyType _t1, AllyType _t2);

	//计算t波敌人的CD
	static int getWaveTime(int t);

	//检查鼠标是否在某方形范围内
	static bool checkMouseInRange(int _x1, int _y1, int _x2, int _y2);
};

