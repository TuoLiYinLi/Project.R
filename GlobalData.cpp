#include "GlobalData.h"

//初始化SDL框架变量
SDL_Window* GlobalData::win = nullptr;
SDL_Renderer* GlobalData::renderer = nullptr;
SDL_Event GlobalData::evt;
TTF_Font* GlobalData::font = nullptr;
bool GlobalData::quitFlag = false;
//每秒多少帧（次数渲染）
Uint32 GlobalData::FPS = 0;
//最后记录的上一次时间 SDL_GetTicks
Uint32 GlobalData::lastTicks = 0;
//上一帧到这一帧变化的时间
Uint32 GlobalData::deltaTime = 0;
//逻辑帧倒计时
Uint32 GlobalData::logicFrameCD = 0;
//进行一秒钟一轮的倒数
Uint32 GlobalData::perSecondCountDown = 0;

int GlobalData::KingX = 0;
int GlobalData::KingY = 0;