#include "GlobalData.h"


SDL_Window* GlobalData::sdl_window = nullptr;
SDL_Renderer* GlobalData::sdl_renderer = nullptr;
bool GlobalData::flag_quit = false;
bool GlobalData::flag_stop = true;
bool GlobalData::flag_debug_physics = true;
bool GlobalData::flag_debug_game_info = true;

TimeSpeedType GlobalData::time_speed_type = TimeSpeedType::normal;

Uint32 GlobalData::FPS = 0;

Uint32 GlobalData::rendered_times = 0;

Uint32 GlobalData::last_recorded_ticks = 0;

Uint32 GlobalData::time_delta = 0;

Uint32 GlobalData::time_physics_frames = 0;

Uint32 GlobalData::logic_frame_CD = 0;

Uint32 GlobalData::per_second_CD = 0;


Uint32 GlobalData::logical_interval_time = 16;


void GlobalData::update_time()
{
    //时间系统
    time_delta = SDL_GetTicks() - last_recorded_ticks;
    last_recorded_ticks = SDL_GetTicks();
    rendered_times += 1;
    per_second_CD += time_delta;
    if (per_second_CD >= 1000) {
        per_second_CD -= 1000;
        FPS = rendered_times;
        rendered_times = 0;
    }
    //物理帧时间累积
    if (!flag_stop)
    {
        logic_frame_CD += time_delta;
    }
}


bool GlobalData::getIfLogicGo()
{
    if(logic_frame_CD > logical_interval_time)
    {
        logic_frame_CD -= logical_interval_time;
        time_physics_frames++;
        return true;
    }
    else
        return false;
}

Uint32 GlobalData::getFPS()
{
    return FPS;
}

Uint32 GlobalData::getTimeDelta()
{
    return time_delta;
}

Uint32 GlobalData::getTimePhysicsFrames()
{
    return time_physics_frames;
}

void GlobalData::setTimeSpeed(TimeSpeedType speed_type)
{
    time_speed_type = speed_type;
	switch (speed_type)
	{
    case TimeSpeedType::normal:
        logical_interval_time = 16;
        break;
    case TimeSpeedType::double_speed:
        logical_interval_time = 8;
        break;
    case TimeSpeedType::triple_speed:
        logical_interval_time = 5;
        break;
	}
}

TimeSpeedType GlobalData::getTimeSpeed()
{
    return time_speed_type;
}


idea_UI_inspector* GlobalData::ui_inspector = nullptr;
idea_UI_scope* GlobalData::ui_scope = nullptr;