#pragma once

#include "SDL.h"
#include "EnumAnimationType.h"

class GameObject;
class RenderingSystem;

class AnimationUnit
{
public:
	//创建新的动画元件
	static AnimationUnit* createNew();
	//销毁这个元件
	void destroy() const;

	unsigned short depth;//这个动画元件的深度,在渲染时优先渲染较小深度的图像

	double deltaX;//渲染时的偏移位置Y,以1/16个网格为单位
	double deltaY;//渲染时的偏移位置Y,以1/16个网格为单位

	double x;//渲染的世界坐标位置
	double y;//渲染的世界坐标位置

	double width;//元件显示的宽度
	double height;//元件显示的高度
	
	void setFlip(bool _val);	//设置是否翻转
	SDL_RendererFlip getFlip() const;	//取得是否翻转

	void setTexture(AnimationType type, int time_length, int current);
	SDL_Texture* getTexture() const; //取得对应材质

	static int getCurrentNum();	//获取正在使用内存的动画元件数量

protected:
	static int current_num;//记录一共有多少的动画元件占用内存

	AnimationUnit();
	~AnimationUnit();

	bool flip;//是否横向反转,一般不反转时,角色面朝右边

	SDL_Texture* texture;//持有的材质
};

