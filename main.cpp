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

#include "PhysicsFacility.h"
#include "PhysicsChara.h"
#include "PhysicsProjectile.h"
#include "ProjectilePoint.h"

#include "Facility.h"
#include "Chara.h"
#include "Projectile.h"
#include "ProjectileFlying.h"

int main(int argc, char** argv) {
	std::cout << "Palace Alpha+1 by TheCarmineDepth\ninitiation now start\n" << std::endl;
    

    //���SDL�����Ƿ�ɹ�������
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
     
    //��鴰�ڼ����Ƿ�ɹ�������
    GlobalData::sdl_window = SDL_CreateWindow("Palace Alpha+1 by TheCarmineDepth ", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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


    //ϵͳ��ʼ��
    WorldSystem::getInstance();
    UISystem::getInstance();
    RenderingSystem::getInstance();
    SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_BLEND);

    auto range = PhysicsFacility::createNew();
    range->X = 0;
    range->Y = 0;
    range->bodyX = WORLD_WIDTH;
    range->bodyY = WORLD_HEIGHT;
    range->setFacilityType(BlockingType::air);
    range->renewSignedGrids();
    /*
     */
	{
		auto pf1=PhysicsFacility::createNew();
		pf1->X = 7;
		pf1->Y = 12;
		pf1->setFacilityType(BlockingType::solid);
		pf1->renewSignedGrids();

		pf1 = PhysicsFacility::createNew();
		pf1->X = 5;
		pf1->Y = 8;
		pf1->bodyY = 5;
		pf1->bodyX = 5;
		pf1->setFacilityType(BlockingType::support);
		pf1->renewSignedGrids();

		auto pf2 = PhysicsChara::createNew();
		pf2->X = 6;
		pf2->Y = 0;
		pf2->bodyX = 3;
		pf2->bodyY = 2;
		pf2->renewSignedGrids();

		auto pf3 = PhysicsChara::createNew();
		pf3->X = 6;
		pf3->Y = 0;
		pf3->bodyX = 1;
		pf3->bodyY = 3;
		pf3->can_swim = true;
		pf3->renewSignedGrids();

		auto pf4 = ProjectileFlying::createNew();
		pf4->X = 0;
		pf4->Y = 0;
		pf4->x_v = 0.1;
		pf4->y_v = 0;
		pf4->y_a = 0.005;
		pf4->renewSignedGrids();

		auto pf5 = PhysicsFacility::createNew();
		pf5->X = 9;
		pf5->Y = 10;
		pf5->bodyY = 5;
		pf5->bodyX = 5;
		pf5->setFacilityType(BlockingType::air);
		pf5->renewSignedGrids();
	}

    SDL_Log(u8"--\t--\t--\t--��ʼ�����,��Ϸ����--\t--\t--\t--");

    //��Ϣѭ��
    while (!GlobalData::flag_quit)
    {

        //ʱ��ϵͳ
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
        //����֡ʱ���ۻ�
        if(!GlobalData::time_stop)
        {
			GlobalData::logic_frame_CD += GlobalData::delta_time;
        }

        //���������¼�
        UISystem::getInstance()->pullEvent();
        UISystem::getInstance()->controlGame();
        
        //ÿ16ms����һ���߼�֡
        while (GlobalData::logic_frame_CD > GlobalData::logical_interval_time)
        {
            GlobalData::logic_frame_CD -= GlobalData::logical_interval_time;
            
            WorldSystem::getInstance()->logicGo();
        }

        //��Ⱦϵͳ
        RenderingSystem::getInstance()->renewViewPosition();
        
        
        //��Ⱦ������ɫ
        SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 14, 80, 81, 255);
        SDL_RenderClear(GlobalData::sdl_renderer);

        //��Ⱦ����
        RenderingSystem::getInstance()->renderAll();

        RenderingSystem::getInstance()->renderALLPhysicsObjects();

        //��������
        //RenderingSystem::getInstance()->renderText_UTF8(u8"���Ĳ���1234(a b c d e f g)",0,0);


        //����˫����
        SDL_RenderPresent(GlobalData::sdl_renderer);
    }

    //��������
    
    SDL_Log(u8"--\t--\t--\t--��������,ֹͣ����--\t--\t--\t--");

    //�ͷŴ���������SDL����
    WorldSystem::destroyInstance();
    UISystem::destroyInstance();
    RenderingSystem::destroyInstance();

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
