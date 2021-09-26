#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
class GlobalData
{
public:
	//初始化SDL框架变量
	static SDL_Window* win ;
	static SDL_Renderer* renderer ;
	static SDL_Event evt;
	static TTF_Font* font;
	static bool quitFlag ;
	//每秒多少帧（次数渲染）
	static Uint32 FPS ;
	//最后记录的上一次时间 SDL_GetTicks
	static Uint32 lastTicks ;
	//上一帧到这一帧变化的时间
	static Uint32 deltaTime ;
	//逻辑帧倒计时
	static Uint32 logicFrameCD ;
	//进行一秒钟一轮的倒数
	static Uint32 perSecondCountDown ;
	
	//魔王的位置X
	static int KingX;

	//魔王的位置Y
	static int KingY;

};

