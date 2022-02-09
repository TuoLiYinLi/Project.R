#include <iostream>
#include "Defined.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
 
#include "Defined.h"
#include "GlobalData.h"
#include "GameToolkit.h"

#include "UISystem.h"
#include "UIObject.h"
#include "UIButton.h"

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

#include "idea_debugger_physics.h"
#include "idea_debugger_game_info.h"
#include "idea_facility_dirt_background.h"
#include "idea_facility_ladder.h"
#include "idea_monster_slime.h"
#include "idea_UI_scope.h"
#include "idea_UI_inspector.h"
#include "idea_UI_button_exit.h"

void test()
{
    SDL_Log("callback");
}

void test_init()
{
    auto f1 = idea_facility_ladder::createNew();
    f1->setPosition(5, 6);

    auto pf2 = idea_monster_slime::createNew();
    pf2->setPosition(7, 2);

    f1 = idea_facility_ladder::createNew();
    f1->setPosition(6, 6);

    f1 = idea_facility_ladder::createNew();
    f1->setPosition(7, 7);

    //UIObject测试
    const auto test_button = idea_UI_button_exit::createNew();
    test_button->setCallback(test);
    test_button->setPosition(500, 300, 18, 18);

    for (int x = 0; x < 5; ++x)
    {
	    for (int y = 0; y < 4; ++y)
	    {
            auto f2 = idea_facility_dirt_background::createNew();
            f2->setPosition(8 + x, 8 + y);
	    }
    }
}

void test_physics()
{
	
}

void test_rendering()
{
	
}


int main(int argc, char** argv) {
	std::cout << u8"Goldust Palace DEMO +1 by TheCarmineDepth\n" << std::endl;
    //检查SDL加载是否成功，报错
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    //检查窗口加载是否成功，报错
    GlobalData::sdl_window = SDL_CreateWindow(u8"Goldust Palace DEMO +1 by TheCarmineDepth", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

    //设置SDL_Log优先级
#ifdef _DEBUG
    SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR);
#endif

    //系统初始化
    WorldSystem::getInstance();
    UISystem::getInstance();
    RenderingSystem::getInstance();

    //测试版水印
    auto const version_mark = RenderingText::createNew();
    version_mark->reference = RenderingReference::window;
	version_mark->setTexture(L"Goldust Palace DEMO +1 by TheCarmineDepth",1, { 255,255,255,255 });
    version_mark->depth = DEPTH_EXTRA + 5;
    version_mark->x = WINDOW_WIDTH - version_mark->width;
    version_mark->y = WINDOW_HEIGHT - version_mark->height;

    //物理层调试器
    auto debugger_physics = idea_debugger_physics::createNew();
    auto debugger_game_info = idea_debugger_game_info::createNew();

    //游戏UI初始化
    GlobalData::ui_scope = idea_UI_scope::createNew();
    GlobalData::ui_inspector = idea_UI_inspector::createNew();

    //代码测试
    test_init();
	

    SDL_Log(u8"--\t--\t--\t--初始化完成,游戏运行--\t--\t--\t--");

    //消息循环
    while (!GlobalData::flag_quit)
    {

        //时间系统
        GlobalData::update_time();

        //处理输入事件
        UISystem::getInstance()->pullEvent();
        UISystem::getInstance()->controlGame();

	    RenderingSystem::getInstance()->renewViewPosition();

        //UI触发
        UISystem::getInstance()->trigger_UIObjects();

        //每16ms运行一次逻辑帧
        while (GlobalData::getIfLogicGo())
        {
            WorldSystem::getInstance()->logicGo();
            //代码测试
            test_physics();
        }


        //渲染时更新
        WorldSystem::getInstance()->logicGoOnRendering();

        //渲染系统
        {
            SDL_SetRenderTarget(GlobalData::sdl_renderer, nullptr);
	        //渲染背景颜色
	        SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 14, 80, 81, 255);
	        SDL_RenderClear(GlobalData::sdl_renderer);

            //测试代码
            test_rendering();

	        //渲染内容
	        //画面渲染

	        RenderingSystem::getInstance()->sortRenderingUnits();
			RenderingSystem::getInstance()->renderAll();
            
	        //交换双缓冲
	        SDL_RenderPresent(GlobalData::sdl_renderer);
        }
    }

    //结束清理
    
    SDL_Log(u8"--\t--\t--\t--停止运行,开始清理--\t--\t--\t--");

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
