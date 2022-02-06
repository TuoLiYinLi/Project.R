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
#include "idea_monster_slime.h"
#include "idea_UI_scope.h"

int main(int argc, char** argv) {
	std::cout << u8"Goldust Palace DEMO +1 by TheCarmineDepth\n" << std::endl;
    

    //���SDL�����Ƿ�ɹ�������
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
     
    //��鴰�ڼ����Ƿ�ɹ�������
    GlobalData::sdl_window = SDL_CreateWindow(u8"Goldust Palace DEMO +1 by TheCarmineDepth", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (GlobalData::sdl_window == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    //�����Ⱦ�������Ƿ�ɹ�������
    GlobalData::sdl_renderer = SDL_CreateRenderer(GlobalData::sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (GlobalData::sdl_renderer == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    //����TTF
    if (TTF_Init() == -1)
    {
        std::cout << TTF_GetError() << std::endl;
        return 1;
    }
    //���ô���ͼ��

    //����SDL_Log���ȼ�
#ifdef _DEBUG
    SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR);
#endif



    //ϵͳ��ʼ��
    WorldSystem::getInstance();
    UISystem::getInstance();
    RenderingSystem::getInstance();

    //���԰�ˮӡ
    auto const version_mark = RenderingText::createNew();
    version_mark->reference = RenderingReference::window;
	version_mark->setTexture(u8"Goldust Palace DEMO +1 by TheCarmineDepth", { 255,255,255,255 }, 1);
    version_mark->depth = RENDERING_DEPTH_EXTRA + 5;
    version_mark->x = WINDOW_WIDTH - version_mark->width;
    version_mark->y = WINDOW_HEIGHT - version_mark->height;

    //����������
    auto debugger_physics = idea_debugger_physics::createNew();
    auto debugger_game_info = idea_debugger_game_info::createNew();

    //��ϷUI��ʼ��
    GlobalData::ui_scope = idea_UI_scope::createNew();
    GlobalData::ui_inspector = idea_UI_inspector::createNew();

    /*
     */
	    auto range = PhysicsFacility::createNew();
	    range->X = 10;
	    range->Y = 2;
	    range->bodyX = 10;
	    range->bodyY = 10;
	    range->setFacilityType(BlockingType::air);
	    range->renewSignedGrids();
    //��ʱ����-���ò���ģ��
	
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

        

        auto pf2 = idea_monster_slime::createNew();
        pf2->setPosition(7, 2);

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
	

    SDL_Log(u8"--\t--\t--\t--��ʼ�����,��Ϸ����--\t--\t--\t--");

    //��Ϣѭ��
    while (!GlobalData::flag_quit)
    {

        //ʱ��ϵͳ
        GlobalData::update_time();

        //���������¼�
        UISystem::getInstance()->pullEvent();
        UISystem::getInstance()->controlGame();

	    RenderingSystem::getInstance()->renewViewPosition();
        
        //ÿ16ms����һ���߼�֡
        while (GlobalData::getIfLogicGo())
        {
            WorldSystem::getInstance()->logicGo();
        }


        //��Ⱦʱ����
        WorldSystem::getInstance()->logicGoOnRendering();

        //��Ⱦϵͳ
        {
            SDL_SetRenderTarget(GlobalData::sdl_renderer, nullptr);
	        //��Ⱦ������ɫ
	        SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 14, 80, 81, 255);
	        SDL_RenderClear(GlobalData::sdl_renderer);

	        //��Ⱦ����
	        //������Ⱦ

	        RenderingSystem::getInstance()->sortRenderingUnits();
			RenderingSystem::getInstance()->renderAll();
            
	        //����˫����
	        SDL_RenderPresent(GlobalData::sdl_renderer);
        }
    }

    //��������
    
    SDL_Log(u8"--\t--\t--\t--��������,ֹͣ����--\t--\t--\t--");

    //�ͷŴ���������SDL����
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
