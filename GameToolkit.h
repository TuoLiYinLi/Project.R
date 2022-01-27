#pragma once
class GameToolkit
{
public:
	//将世界坐标转换为窗口坐标
	static void transPositionWorldToWindow(double x_world,double y_world,double* x_window,double* y_window);
	//将窗口坐标转换为世界坐标
	static void transPositionWindowToWorld(double x_window, double y_window, double* x_world, double* y_world);

	//计算str中共有多少字符以及含有多少1/2/3位的字符(共4位)
	static void getLengthUTF8(char const* str, int* cnt);
};

