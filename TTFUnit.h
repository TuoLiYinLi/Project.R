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
	SDL_Color color;//颜色信息
	double world_x;//世界坐标_X
	double world_y;//世界坐标_Y
	double scale;//缩放系数
	unsigned short depth;
	int w;
	int h;
	
	SDL_Texture* texture;//创建的纹理

	//设置显示位置
	void set(double x,double y);

	static TTFUnit* createNew(const char* _message, SDL_Color _color);
	void destroy();

	//获取当前正在占用内存的文字单元数量
	static int getCurrentNum();
protected:
	static int currentNum;//记录一共有多少的文字元件占用内存
	TTFUnit(const char* _message, SDL_Color _color);
	~TTFUnit();
};

