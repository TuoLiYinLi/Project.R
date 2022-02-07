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

class RenderingSystem
{


public:
	TTF_Font* font_silver;//字体Silver.ttf

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

	//对字体初始化

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

	SDL_Texture* font_unicode_map;//保存Unicode重新映射后的字表材质

	void createUnicodeMap(const char* _save_file);//创建一个Unicode字表

	static  SDL_Rect getMappingRect(Uint16 num, int total_rows, int font_width, int font_height, int  grid_width, int grid_height);//获取编号在font_unicode_map中的位置

	static Uint16 remappingUnicodeRule(Uint16 unicode_char);//将Unicode字符重新映射一个数值

	static bool compareDepth(const RenderingUnit* ru1, const RenderingUnit* ru2);//比较两个渲染单元的大小,用于排序回调函数

	Uint16 unicode_range_min;//重映射字体Unicode最小值
	Uint16 unicode_range_max;//重映射字体Unicode最大值

	int remapping_grid_width;//重映射格位宽
	int remapping_grid_height;//重映射格位高
	int remapping_total_rows;//重映射总行数
};

