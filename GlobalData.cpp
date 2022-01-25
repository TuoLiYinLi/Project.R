#include "GlobalData.h"


SDL_Window* GlobalData::sdl_window = nullptr;
SDL_Renderer* GlobalData::sdl_renderer = nullptr;
bool GlobalData::flag_quit = false;

Uint32 GlobalData::FPS = 0;

Uint32 GlobalData::last_recorded_ticks = 0;

Uint32 GlobalData::delta_time = 0;

Uint32 GlobalData::logic_frame_CD = 0;

Uint32 GlobalData::per_second_CD = 0;

bool GlobalData::time_stop = true;

Uint32 GlobalData::logical_interval_time = 16;

bool GlobalData::debug_physics = true;