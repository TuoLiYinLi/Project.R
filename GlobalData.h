#pragma once
#include "SDL.h"

class GlobalData
{
public:
	static SDL_Window* sdl_window;	//sdl����
	static SDL_Renderer* sdl_renderer;	//sdl��Ⱦ��

	static bool flag_quit;	//�˳���־

	static Uint32 FPS;		//ÿ�����֡��������Ⱦ��

	static Uint32 last_recorded_ticks;		//���һ�ν��м�¼��ʱ�� SDL_GetTicks

	static Uint32 delta_time;	//��һ֡����һ֡�仯��ʱ��

	static Uint32 logical_interval_time;	//��һ����֡����һ����֡��ʱ����

	static Uint32 per_second_CD;//����һ����һ�ֵĵ���

	static bool time_stop;//ʱ�����ŵ��ٶ�

	static Uint32 logic_frame_CD;	//�߼�֡����ʱ

	static bool debug_physics;	//�Ƿ�������debug
};

