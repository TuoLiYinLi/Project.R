#pragma once
#include "SDL.h"

class idea_UI_sizer;
class idea_UI_energy;
class idea_UI_button_menu;
class idea_UI_speed_controller;
class idea_UI_scope;
class idea_UI_inspector;

enum class TimeSpeedType
{
	normal = 1,
	double_speed = 2,
	triple_speed = 3,
};

//ȫ������
class GlobalData
{
public:
	static SDL_Window* sdl_window;	//sdl����
	static SDL_Renderer* sdl_renderer;	//sdl��Ⱦ��

	static bool flag_quit;	//�˳���־
	static bool flag_stop;//ʱ���Ƿ���ͣ
	static bool flag_debug_physics;	//�Ƿ���������ʾdebug
	static bool flag_debug_game_info;//�Ƿ�����Ϸ��Ϣdebug


	static Uint32 getFPS();

	static Uint32 getTimePhysicsFrames();//��ȡ��ǰ������֡ʱ��

	static Uint32 getTimeDelta();//��ȡ��һ֡����һ֡�仯��ʱ��

	static  void update_time();//ˢ��ʱ��

	static bool getIfLogicGo();//����Ƿ�����ƽ��߼�,����ʱ��Ϊ����������֡

	static void setTimeSpeed(TimeSpeedType speed_type);

	static TimeSpeedType getTimeSpeed();


	static idea_UI_inspector* ui_inspector;//UI�����
	static idea_UI_scope* ui_scope;//UIѡ�п�
	static idea_UI_speed_controller* ui_speed_controller;//UI�ٶȿ�����
	static idea_UI_button_menu* ui_menu_button;//UI�򿪲˵���ť
	static idea_UI_energy* ui_energy;//ui������
	static idea_UI_sizer* ui_sizer;//uiɸѡ��

protected:
	static Uint32 FPS;		//ÿ�����֡��������Ⱦ��

	static Uint32 rendered_times;		//��1������Ⱦ�Ĵ���

	static Uint32 time_physics_frames;//��ǰ������֡ʱ��

	static Uint32 time_delta;	//��һ֡����һ֡�仯��ʱ��

	static Uint32 logic_frame_CD;	//�߼�֡����ʱ

	static Uint32 last_recorded_ticks;		//���һ�ν��м�¼��ʱ�� SDL_GetTicks

	static Uint32 logical_interval_time;	//��һ����֡����һ����֡��ʱ����

	static TimeSpeedType time_speed_type;//��Ϸʱ���ٶ�

	static Uint32 per_second_CD;//����һ����һ�ֵĵ���
};

