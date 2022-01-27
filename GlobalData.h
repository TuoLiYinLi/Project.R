#pragma once
#include "SDL.h"

class GlobalData
{
public:
	static SDL_Window* sdl_window;	//sdl窗口
	static SDL_Renderer* sdl_renderer;	//sdl渲染器

	static bool flag_quit;	//退出标志
	static bool flag_stop;//时间是否暂停
	static bool flag_debug_physics;	//是否开启内置debug


	static Uint32 getFPS();

	static Uint32 getTimePhysicsFrames();//获取当前的物理帧时间

	static Uint32 getTimeDelta();//获取上一帧到这一帧变化的时间

	static  void update_time();//刷新时间

	static bool getIfLogicGo();//检查是否可以推进逻辑,调用时视为运行了物理帧

protected:
	static Uint32 FPS;		//每秒多少帧（次数渲染）

	static Uint32 time_physics_frames;//当前的物理帧时间

	static Uint32 time_delta;	//上一帧到这一帧变化的时间

	static Uint32 logic_frame_CD;	//逻辑帧倒计时

	static Uint32 last_recorded_ticks;		//最后一次进行记录的时间 SDL_GetTicks

	static Uint32 logical_interval_time;	//上一物理帧到这一物理帧的时间间隔

	static Uint32 per_second_CD;//进行一秒钟一轮的倒数

};

