#include <iostream>
#include "Defined.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
 
#include "GlobalData.h"
#include "Defined.h"

#include "UISystem.h"
#include "WorldSystem.h"

#include "RenderingSystem.h"
#include "RenderingText.h"

#include "PhysicsFacility.h"
#include "PhysicsChara.h"
#include "PhysicsProjectile.h"

#include "Facility.h"
#include "Chara.h"
#include "Projectile.h"

#include "ProjectilePoint.h"
#include "ProjectileFlying.h"

int main(int argc, char** argv) {
	std::cout << u8"Palace Alpha+1 by TheCarmineDepth\ninitiation now start\n" << std::endl;
    

    //检查SDL加载是否成功，报错
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
     
    //检查窗口加载是否成功，报错
    GlobalData::sdl_window = SDL_CreateWindow(u8"Palace Alpha+1 by TheCarmineDepth ", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
    UISystem::getInstance();
    RenderingSystem::getInstance();
    SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_BLEND);

    //测试版水印
    auto const version_mark = RenderingText::createNew();
    version_mark->reference = RenderingReference::window;
	version_mark->setTexture(u8"Palace DEMO Alpha+1 by TheCarmineDepth", { 255,255,255,255 }, 1);
    version_mark->depth = RENDERING_DEPTH_EXTRA + 1;
    version_mark->x = WINDOW_WIDTH - version_mark->width;
    version_mark->y = WINDOW_HEIGHT - version_mark->height;

    /*
    auto range = PhysicsFacility::createNew();
    range->X = 0;
    range->Y = 0;
    range->bodyX = WORLD_WIDTH;
    range->bodyY = WORLD_HEIGHT;
    range->setFacilityType(BlockingType::air);
    range->renewSignedGrids();
     */
    //临时测试-设置测试模型
	
		auto pf1=PhysicsFacility::createNew();
		pf1->X = 7;
		pf1->Y = 12;
        pf1->bodyX = 50;
		pf1->setFacilityType(BlockingType::solid);
		pf1->renewSignedGrids();

		pf1 = PhysicsFacility::createNew();
		pf1->X = 5;
		pf1->Y = 8;
		pf1->bodyY = 5;
		pf1->bodyX = 5;
		pf1->setFacilityType(BlockingType::support);
		pf1->renewSignedGrids();

        auto pf2 = Chara::createNew();
        pf2->getPhysicsChara()->setPosition(7, 2);

        /*
		auto pf4 = ProjectileFlying::createNew();
		pf4->X = 0;
		pf4->Y = 0;
		pf4->x_v = 0.1;
		pf4->y_v = 0;
		pf4->y_a = 0.005;
		pf4->renewSignedGrids();
         */

		auto pf5 = PhysicsFacility::createNew();
		pf5->X = 9;
		pf5->Y = 10;
		pf5->bodyY = 5;
		pf5->bodyX = 5;
		pf5->setFacilityType(BlockingType::air);
		pf5->renewSignedGrids();
	

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
        if(!GlobalData::time_stop)
        {
			GlobalData::logic_frame_CD += GlobalData::delta_time;
        }

        //处理输入事件
        UISystem::getInstance()->pullEvent();
        UISystem::getInstance()->controlGame();
        
        //每16ms运行一次逻辑帧
        while (GlobalData::logic_frame_CD > GlobalData::logical_interval_time)
        {
            GlobalData::logic_frame_CD -= GlobalData::logical_interval_time;
            
            WorldSystem::getInstance()->logicGo();
            //SDL_Log(u8"%d", pf2->animation_progress);
        }

        //渲染系统
        RenderingSystem::getInstance()->renewViewPosition();
        
        
        //渲染背景颜色
        SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 14, 80, 81, 255);
        SDL_RenderClear(GlobalData::sdl_renderer);

        //渲染内容
        //画面渲染

        RenderingSystem::getInstance()->sortRenderingUnits();
		RenderingSystem::getInstance()->renderAll();

    	//物理debug渲染
        if(GlobalData::debug_physics)
        {
			RenderingSystem::getInstance()->renderALLPhysicsObjects();
        }
        

        //交换双缓冲
        SDL_RenderPresent(GlobalData::sdl_renderer);
    }

    //结束清理
    
    SDL_Log(u8"--\t--\t--\t--结束清理,停止运行--\t--\t--\t--");

    //释放创建的所有SDL内容
    RenderingSystem::destroyInstance();
    UISystem::destroyInstance();
    WorldSystem::destroyInstance();

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
