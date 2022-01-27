#pragma once
#include "SDL.h"

enum class RenderingReference
{
	window,//窗口参考系
	world,//世界参考系
};

class RenderingUnit
{
public:
	//创建新的动画元件
	static class RenderingUnit* createNew();
	//销毁这个元件
	virtual void destroy() const;

	RenderingReference reference;	//这个元件的位置参考系

	bool flag_enable;//是否渲染

	float depth;//这个渲染元件的深度,在渲染时优先渲染较小深度的图像

	double x;//渲染的世界坐标位置
	double y;//渲染的世界坐标位置

	double deltaX;//渲染时的偏移位置Y,以1/16个网格为单位
	double deltaY;//渲染时的偏移位置Y,以1/16个网格为单位

	double width;//元件显示的宽度
	double height;//元件显示的高度

	void setFlip(bool _val);	//设置是否翻转
	SDL_RendererFlip getFlip() const;	//取得是否翻转

	void setTexture(SDL_Texture* _texture);
	SDL_Texture* getTexture() const; //取得对应材质

	static int getRenderingUnitNum();	//获取正在使用内存的渲染元件数量

protected:

	RenderingUnit();
	virtual ~RenderingUnit();

	bool flip;//是否横向反转,一般不反转时,角色面朝右边

	SDL_Texture* texture;//持有的材质

private:
	static int rendering_unit_num;//记录一共有多少的渲染元件占用内存
};

