#pragma once

#include <vector>
#include <list>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "RenderingUnit.h"

#include "EnumAnimationType.h"

class PhysicsObject;

class RenderingAnimation;

//渲染系统
class RenderingSystem
{
public:
	TTF_Font* font_grey;//字体grey.ttf

	//获取单例实例
	static RenderingSystem* getInstance();

	//销毁和析构
	static void destroyInstance();

	void add(RenderingUnit* ru)const;

	void remove(RenderingUnit* ru)const;

	//加载某一种动画资源
	void loadAnimation( AnimationType antp)const;
	//加载所有种类的动画资源
	void loadAllAnimation()const;
	//卸载某一种动画资源
	void unloadAnimation(AnimationType antp) const;
	//卸载所有种类的动画资源
	void unloadAllAnimation()const;

	//渲染单个的渲染单元
	void renderOneUnit(const RenderingUnit* au) const;

	//对RenderingUnits重新排序
	void sortRenderingUnits() const;

	//渲染所有动画单元(跳过不需要渲染的部分)
	void renderAll() const;
	
	SDL_Texture* getAnimation(AnimationType _animation_type,unsigned long long num)const;
	unsigned long long getAnimationSize(AnimationType _animation_type)const;

	//改变视口位置
	void renewViewPosition();

	double window_width;//窗口宽度
	double window_height;//窗口高度

	double vy;//窗口的Y坐标改变速度
	double vx;//窗口的X坐标改变速度
	double vs;//窗口的缩放水平改变速度

	double viewX;//窗口的X世界坐标
	double viewY;//窗口的Y世界坐标
	double viewScale;//窗口的缩放水平

protected:
	RenderingSystem();
	~RenderingSystem();

	static RenderingSystem* instance;//单例实例

	std::list<RenderingUnit*>* list_rendering_units;//动画单元列表,储存需要渲染的动画元件
	std::vector<std::vector<SDL_Texture*>*>* list_animation_texture;//一个二维的材质列表,用于加载所有的动画资源

	static bool compareDepth(const RenderingUnit* ru1, const RenderingUnit* ru2);//比较两个渲染单元的大小,用于排序回调函数
};

