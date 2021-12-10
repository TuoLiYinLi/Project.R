#include <iostream>
#include "Defined.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
 
#include "GlobalData.h"

#include "InputSystem.h"
#include "WorldSystem.h"

#include "PhysicsChara.h"
#include "Facility.h"

int main(int argc, char** argv) {
	std::cout << "Palace Alpha 2 by TheCarmineDepth\ninitiation now start\n" << std::endl;
    

    //检查SDL加载是否成功，报错
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
     
    //检查窗口加载是否成功，报错
    GlobalData::sdl_window = SDL_CreateWindow("Palace Alpha 2 by TheCarmineDepth ", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (GlobalData::sdl_window == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    //检查渲染器加载是否成功，报错
    GlobalData::sdl_renderer = SDL_CreateRenderer(GlobalData::sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (GlobalData::sdl_renderer == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    //加载TTF
    if (TTF_Init() == -1)
    {
        std::cout << TTF_GetError() << std::endl;
        return 1;
    }
    //设置窗口图标


    //系统初始化
    WorldSystem::getInstance();
    InputSystem::getInstance();

    Facility::createNew();


    SDL_Log(u8"--\t--\t--\t--初始化完成,游戏运行--\t--\t--\t--");


    //消息循环
    while (!GlobalData::flag_quit)
    {

        //时间系统
        GlobalData::delta_time = SDL_GetTicks() - GlobalData::last_recorded_ticks;
        GlobalData::last_recorded_ticks = SDL_GetTicks();
        GlobalData::FPS += 1;
        GlobalData::per_second_CD += GlobalData::delta_time;
        if (GlobalData::per_second_CD >= 1000) {
#ifdef SHOW_FPS
            std::cout << "FPS:" << GlobalData::FPS << std::endl;
#endif // SHOW_FPS
            GlobalData::per_second_CD -= 1000;
            GlobalData::FPS = 0;
        }
        //物理帧时间累积
        GlobalData::logic_frame_CD += GlobalData::delta_time;

        //处理输入事件
        InputSystem::getInstance()->handleEvent();

        //每16ms运行一次逻辑帧
        while (GlobalData::logic_frame_CD > 16)
        {
            GlobalData::logic_frame_CD -= 16;
            
            WorldSystem::getInstance()->logicGo();
        }
        //渲染系统
        //渲染背景颜色
        SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 14, 80, 81, 255);
        SDL_RenderClear(GlobalData::sdl_renderer);

        //渲染内容
        //worldSystem-> animSys->renderAll();

        //交换双缓冲
        SDL_RenderPresent(GlobalData::sdl_renderer);
    }

    //结束清理
    
    SDL_Log(u8"--\t--\t--\t--结束清理,停止运行--\t--\t--\t--");

    //释放创建的所有SDL内容
    //inputSystem->destroyInstance();
    WorldSystem::destroyInstance();
    InputSystem::destroyInstance();

    if (GlobalData::sdl_renderer) {
        SDL_DestroyRenderer(GlobalData::sdl_renderer);
    }

    if (GlobalData::sdl_window) {
        SDL_DestroyWindow(GlobalData::sdl_window);
    }
    
    TTF_Quit();
    SDL_Quit();
    return 0;
}
