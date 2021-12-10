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
    

    //���SDL�����Ƿ�ɹ�������
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
     
    //��鴰�ڼ����Ƿ�ɹ�������
    GlobalData::sdl_window = SDL_CreateWindow("Palace Alpha 2 by TheCarmineDepth ", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
    InputSystem::getInstance();

    Facility::createNew();


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
        GlobalData::logic_frame_CD += GlobalData::delta_time;

        //���������¼�
        InputSystem::getInstance()->handleEvent();

        //ÿ16ms����һ���߼�֡
        while (GlobalData::logic_frame_CD > 16)
        {
            GlobalData::logic_frame_CD -= 16;
            
            WorldSystem::getInstance()->logicGo();
        }
        //��Ⱦϵͳ
        //��Ⱦ������ɫ
        SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 14, 80, 81, 255);
        SDL_RenderClear(GlobalData::sdl_renderer);

        //��Ⱦ����
        //worldSystem-> animSys->renderAll();

        //����˫����
        SDL_RenderPresent(GlobalData::sdl_renderer);
    }

    //��������
    
    SDL_Log(u8"--\t--\t--\t--��������,ֹͣ����--\t--\t--\t--");

    //�ͷŴ���������SDL����
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
