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
#include "PhysicsProjectilePoint.h"
#include "PhysicsProjectileFlying.h"

#include "idea_debugger_physics.h"
#include "idea_debugger_game_info.h"
#include "idea_facility_dirt_background.h"
#include "idea_facility_ladder.h"
#include "idea_monster_slime.h"
#include "idea_particle_dizzy.h"
#include "idea_particle_flame.h"
#include "idea_particle_goldust.h"
#include "idea_particle_poisoned.h"
#include "idea_projectile_chop.h"
#include "idea_UI_scope.h"
#include "idea_UI_inspector.h"
#include "idea_UI_inspector_exit.h"
#include "idea_UI_button_menu.h"
#include "idea_UI_speed_controller.h"
#include "idea_UI_energy.h"
#include "idea_UI_sizer.h"
#include "integrate_particles_maker.h"
#include "Particle.h"
#include "UIScroll.h"

void test()
{
    SDL_Log("callback");
}

void test_init()
{
    auto pf2 = idea_monster_slime::createNew();
    pf2->setPosition(7, 7);

    //pf2->effect_burning = 600;
    //pf2->effect_blind = 60;
    //pf2->effect_charging = 6000;
    //pf2->effect_dizzy = 6000;
    //pf2->effect_poisoned = 600;
    //pf2->effect_resistant = 60;
    //pf2->effect_sealed = 60;
    
    pf2 = idea_monster_slime::createNew();
    pf2->setPosition(8, 7);
    pf2->health = 2;
     
    auto f1 = idea_facility_ladder::createNew();
    f1->setPosition(5, 6);
    

    f1 = idea_facility_ladder::createNew();
    f1->setPosition(8, 6);

    f1 = idea_facility_ladder::createNew();
    f1->setPosition(7, 7);

    /*
    //UIObject测试
    UIObject::createNew();

    auto r= RenderingUnit::createNew();

    r->x = 200;
    r->y = 200;
    r->width = 200;
    r->height = 100;
    r->setTexture(RenderingSystem::getInstance()->getAnimation(AnimationType::debug_sequence_white, 1));
    r->flag_enable = true;
    r->reference = RenderingReference::window;

    const auto test_button2 = idea_UI_speed_controller::createNew();
    

    //泥土
    for (int x = 0; x < 5; ++x)
    {
	    for (int y = 0; y < 4; ++y)
	    {
            auto f2 = idea_facility_dirt_background::createNew();
            f2->setPosition(8 + x, 8 + y);
	    }
    }

    //测试scroll

    auto scroll= UIScroll::createNew();
    int w, h;
    auto text0 = GameToolkit::createUnicodeText(L"测试一下我的卷轴中文排版是否存在一些问题是否需要改变间距", { 255,255,255,150 }, 60, &w, &h);

    scroll->setup(text0, 500, 400, w, h, 100, 30, 50, 8, 500);
    scroll->enable();
     */

    idea_projectile_chop::createNew()->setup(AllyType::monster,7,7,CharaDirection::right, false);

    //auto particle = idea_particle_goldust::createNew();
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
    version_mark->depth = depth_extra + 5;
    version_mark->x = WINDOW_WIDTH - version_mark->width - 4;
    version_mark->y = WINDOW_HEIGHT - version_mark->height + 6;

    //物理层调试器
    idea_debugger_physics::createNew();
    idea_debugger_game_info::createNew();

    //游戏UI初始化
    GlobalData::ui_scope = idea_UI_scope::createNew();
    GlobalData::ui_inspector = idea_UI_inspector::createNew();
    GlobalData::ui_menu_button = idea_UI_button_menu::createNew();
    GlobalData::ui_speed_controller = idea_UI_speed_controller::createNew();
    GlobalData::ui_energy = idea_UI_energy::createNew();
    GlobalData::ui_sizer = idea_UI_sizer::createNew();

    //代码测试
    test_init();
	
    auto pm = integrate_particles_maker<idea_particle_dizzy>();
    pm.update(1, 120, 0, 0.5, 0.5, 0, 0, 0, -0.5 * pi,0.5*pi);

	SDL_Log(u8"--\t--\t--\t--初始化完成,游戏运行--\t--\t--\t--");

    //消息循环
    while (!GlobalData::flag_quit)
    {
	    //时间系统
    	{
    		GlobalData::update_time();

    		//处理输入事件
    		UISystem::getInstance()->pullEvent();

    		RenderingSystem::getInstance()->renewViewPosition();

    		//UI触发
    		UISystem::getInstance()->trigger_UIObjects();
    		//UI介入游戏逻辑
    		UISystem::getInstance()->controlGame();
		}

        //每16ms运行一次逻辑帧
        while (GlobalData::getIfLogicGo())
        {
            WorldSystem::getInstance()->logicGo();
            //代码测试
            test_physics();
            pm.make_particle();
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
            //test_rendering();

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
