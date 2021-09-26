#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "GlobalData.h"

#include "AnimType.h"
#include "AnimationUnit.h"
class AnimationUnit;
#include "TTFUnit.h"
class TTFUnit;

class AnimSystem
{
public:
	std::vector<std::vector<SDL_Texture*>*>* animList;//一个二维的材质列表,用于加载所有的动画资源
	std::list<AnimationUnit*>* animUnitList;//动画单元列表,储存需要渲染的动画元件
	std::list<TTFUnit*>* fontUnitList;//字体单元列表

	//获取单例实例
	static AnimSystem* getInstance();
	//销毁和析构
	void destroyInstance();

	//去除动画元件
	void removeAnimUnit(AnimationUnit* _animUnit);

	//去除文字元件
	void removeTTFUnit(TTFUnit* _TTFUnit);

	//加载某一种动画资源
	void loadAnim( AnimType antp);
	//加载所有种类的动画资源
	void loadAllAnim();
	//卸载某一种动画资源
	void unloadAnim(AnimType antp);
	//卸载所有种类的动画资源
	void unloadAllAnim();

	//渲染单个的动画单元
	void renderOneUnit(AnimationUnit* au);
	//渲染单个的动画单元
	void renderOneUnit(TTFUnit* tu);
	//渲染所有动画单元(跳过不需要渲染的部分)
	void renderAll();
	//更新窗口位置
	void updateWindow();

	double vy;//窗口的Y坐标改变速度
	double vx;//窗口的X坐标改变速度
	double vs;//窗口的缩放水平改变速度

	double viewX;//窗口的X世界坐标
	double viewY;//窗口的Y世界坐标
	double viewScale;//窗口的缩放水平

protected:

	
	//获取动画单元的动画种类所对应的材质资源
	SDL_Texture* getTextureFromAU(AnimationUnit* au);
	//单例实例
	static AnimSystem* instance;
	AnimSystem();
	~AnimSystem();

	double windowWidth;//窗口宽度
	double windowHeight;//窗口高度
};

