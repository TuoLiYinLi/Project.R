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
	unsigned short depth;//这个动画元件的深度,在渲染时优先渲染较小深度的图像

	AnimType type;//这个动画元件的类型,说明了是什么动画
	int animProgress;//表示渲染这个动画的第几帧

	double deltaX;//渲染时的偏移位置Y,以1/16个网格为单位
	double deltaY;//渲染时的偏移位置Y,以1/16个网格为单位

	double x;//渲染的世界坐标位置
	double y;//渲染的世界坐标位置

	double width;//元件显示的宽度
	double height;//元件显示的高度

	double angle;//元件绕中心点旋转的角度,角度制度
	SDL_RendererFlip flip;//是否横向反转,一般不反转时,角色面朝右边

	//设置动画元件的显示位置和状态
	AnimationUnit* set(double _x,double _y,double _width=-1,double _height=-1,double _angle=0);

	//创建新的动画元件
	static AnimationUnit* createNew();
	//销毁这个元件
	void destroy();
	//获取正在使用内存的动画元件数量
	static int getCurrentNum();

protected:
	static int currentNum;//记录一共有多少的动画元件占用内存
	AnimationUnit();
	~AnimationUnit();
};

