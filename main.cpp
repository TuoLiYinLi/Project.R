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
#include "idea_facility_dirt_cracked.h"
#include "idea_facility_dirt_solid.h"
#include "idea_facility_ladder.h"
#include "idea_facility_mucus.h"
#include "idea_facility_water_clean.h"
#include "idea_monster_slime.h"
#include "idea_particle_dizzy.h"
#include "idea_particle_flame.h"
#include "idea_particle_goldust.h"
#include "idea_particle_poisoned.h"
#include "idea_projectile_chop.h"
#include "idea_projectile_little_slime_ball.h"
#include "idea_UI_scope.h"
#include "idea_UI_inspector.h"
#include "idea_UI_inspector_exit.h"
#include "idea_UI_button_menu.h"
#include "idea_UI_speed_controller.h"
#include "idea_UI_energy.h"
#include "idea_UI_sizer.h"
#include "idea_warrior_miner.h"
#include "integrate_particles_maker.h"
#include "Particle.h"
#include "UIScroll.h"

void test_map()
{
    //生成背景
	for (int x = 0; x < 32; ++x)
	{
		for (int y = 0; y < 32; ++y)
		{
            const auto bg = idea_facility_dirt_background::createNew();
            bg->setPosition(x, y);
		}
	}
    for (int x = 0; x < 32; ++x)
    {
        const auto d = idea_facility_dirt_solid::createNew();
        d->setPosition(x, 31);
    }

    for (int y = 0; y < 31; ++y)
    {
        auto d = idea_facility_dirt_solid::createNew();
        d->setPosition(0, y);
    	d = idea_facility_dirt_solid::createNew();
        d->setPosition(31, y);
    }
    for (int x = 1; x < 3; ++x)
    {
        for (int y = 9; y < 12; ++y)
        {
            const auto dc = idea_facility_dirt_cracked::createNew();
            dc->setPosition(x, y);
        }
    }
    for (int x = 2; x < 7; ++x)
    {
	    for (int y = 8; y < 13; ++y)
	    {
            const auto dc = idea_facility_dirt_solid::createNew();
            dc->setPosition(x, y);
	    }
    }
    for (int x = 9; x < 12; ++x)
    {
        for (int y = 11; y < 31; ++y)
        {
            if (y == 24)continue;
            const auto dc = idea_facility_dirt_solid::createNew();
            dc->setPosition(x, y);
        }
    }
    for (int x = 12; x < 14; ++x)
    {
        for (int y = 14; y < 31; ++y)
        {
            if (y == 24)continue;
            const auto dc = idea_facility_dirt_solid::createNew();
            dc->setPosition(x, y);
        }
    }
    for (int x = 1; x < 9; ++x)
    {
        for (int y = 25; y < 31; ++y)
        {
            const auto w = idea_facility_water_clean::createNew();
            if (y == 25)w->setWaterTop();
            w->setPosition(x, y);
        }
    }
    for (int x = 14; x < 17; ++x)
    {
        for (int y = 17; y <21; ++y)
        {
            const auto dc = idea_facility_dirt_solid::createNew();
            dc->setPosition(x, y);
        }
    }
    
    for (int y = 17; y < 31; ++y)
    {
        const auto dc = idea_facility_ladder::createNew();
        dc->setPosition(17, y);
    }

    for (int x = 18; x < 30; ++x)
    {
        for (int y = 22; y < 24; ++y)
        {
            const auto dc = idea_facility_dirt_cracked::createNew();
            dc->setPosition(x, y);
        }
    }
    for (int y = 11; y < 14; ++y)
    {
        const auto dc = idea_facility_ladder::createNew();
        dc->setPosition(12, y);
    }
    for (int y = 14; y < 17; ++y)
    {
        const auto dc = idea_facility_ladder::createNew();
        dc->setPosition(14, y);
    }

	{
		const auto m = idea_facility_mucus::createNew();
        m->setPosition(21, 21);
        m->counting_container.addNumOf(CountingType::slime, 8);
	}
}

void test()
{
    SDL_Log("callback");
}

void test_init()
{
	auto pf2 = idea_monster_slime::createNew();
    pf2->setPosition(23, 5);
    pf2->effect_poisoned = 600;
    pf2->gene_container.addGene(GeneMaker::slime_glue());

    pf2 = idea_monster_slime::createNew();
    pf2->setPosition(20, 5);

    //pf2->effect_burning = 300;
    //pf2->effect_blind = 60;
    //pf2->effect_charging = 6000;
    //pf2->effect_dizzy = 6000;
    //pf2->effect_poisoned = 600;
    //pf2->effect_resistant = 60;
    //pf2->effect_sealed = 60;

	const auto pf1 = idea_warrior_miner::createNew();
    pf1->setPosition(22, 20);
    

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
    test_map();
    test_init();
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
