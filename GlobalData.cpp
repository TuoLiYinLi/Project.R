#include "GlobalData.h"


SDL_Window* GlobalData::sdl_window = nullptr;
SDL_Renderer* GlobalData::sdl_renderer = nullptr;
bool GlobalData::flag_quit = false;

Uint32 GlobalData::FPS = 0;

Uint32 GlobalData::last_recorded_ticks = 0;

Uint32 GlobalData::delta_time = 0;

Uint32 GlobalData::logic_frame_CD = 0;

Uint32 GlobalData::per_second_CD = 0;
