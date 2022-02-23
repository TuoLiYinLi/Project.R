#pragma once
#include <string>
#include <SDL.h>
#include "PhysicsObject.h"
#include "integration_gene_container.h"

//静态工具类
class GameToolkit
{
public:
	//将世界坐标转换为窗口坐标
	static void transPositionWorldToWindow(double x_world,double y_world,double* x_window,double* y_window);
	//将窗口坐标转换为世界坐标
	static void transPositionWindowToWorld(double x_window, double y_window, double* x_world, double* y_world);

	//生成一个特定颜色的透明字体,并用指针传递出生成的宽度和高度
	static SDL_Texture* createUnicodeLine(const wchar_t* unicode_str, SDL_Color color, int* width, int* height);
	static SDL_Texture* createUnicodeLine(const wchar_t* unicode_str, SDL_Color color, SDL_Color bg_color, int* width, int* height);
	static SDL_Texture* createUnicodeText(const wchar_t* unicode_str, SDL_Color color, int wrapLength, int* w, int* h);
	static SDL_Texture* createUnicodeText(const wchar_t* unicode_str, SDL_Color color, SDL_Color bg_color, int wrapLength, int* w, int* h);

	//检查两个阵营是否交战(和平阵营永远不敌对,同阵营也不敌对)
	static bool checkIfHostile(AllyType _t1, AllyType _t2);

	//计算t波敌人的CD
	static int getWaveTime(int t);

	//检查鼠标是否在某方形范围内
	static bool checkMouseInRange(int _x1, int _y1, int _x2, int _y2);

	//保留double后小数n位
	static std::wstring double_reserve_decimal(double d, int n);

	//产生随机数在min与max之间
	static double random(double min, double max);

	//产生0到range的随机自然数
	static unsigned random(unsigned range);

	//对原来的bool值进行覆盖操作
	static bool boolOverride(bool ori,OverrideOperation operation);

};

