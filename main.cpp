#include <iostream>
#include "Defined.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "GlobalData.h"

#include "AnimSystem.h"
#include "MapSystem.h"
#include "GeneSystem.h"
#include "CharaSystem.h"
#include "FacilitySystem.h"
#include "ProjectileSystem.h"
#include "ParticleSystem.h"

#include "FacilityStatic.h"
#include "FacilityDirtWall.h"
#include "FacilityDirtBG.h"
#include "FacilityDirtStairL.h"
#include "FacilityDirtStairR.h"
#include "FacilityDirtStairB.h"

#include "FacilityDynamic.h"
#include "FacilityDirtCracked.h"
#include "FacilitySlimeGlue.h"

#include "PenetrableProj.h"
#include "ProjChop.h"

#include "ImmediateProj.h"
#include "ProjSlimeBall.h"

#include "WorldSystem.h"

#include "CharaSlime.h"


#include "InputSystem.h"
#include "GameToolkit.h"

int main(int argc, char** argv) {
	std::cout << "int main(int argc, char** argv)" << std::endl;
    

    //检查SDL加载是否成功，报错
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    //检查窗口加载是否成功，报错
    GlobalData::win = SDL_CreateWindow("Reborn Palace Alpha 1 by TheCarmineDepth ", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (GlobalData::win == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    //检查渲染器加载是否成功，报错
    GlobalData::renderer = SDL_CreateRenderer(GlobalData::win, -1, SDL_RENDERER_ACCELERATED);
    if (GlobalData::renderer == nullptr) {
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
    WorldSystem* worldSystem = WorldSystem::getInstance();
    
    InputSystem* inputSystem = InputSystem::getInstance();
    
    gameToolkit::summonMap_2_0_a(20220925);

    //auto t = worldSystem->animSys->addTTFUnit("1234\n12sadasdda dadsd asw34\n \t\t\ts sad1234\n12453123456\n\n", {255,255,255,255});
    auto t = TTFParticle::createNew();
    t->fontUnit = TTFUnit::createNew("20210925", {255,0,0,255});
    t->livingTime = 200;

    /*
    auto f = FacilityDirtStairR::createNew();
    f->x = 27;
    f->y = 11;
    f->renewPosition();

    auto f1 = FacilityDirtCracked::createNew();
    f1->x = 39;
    f1->y = 10;
    f1->renewPosition();
    */

    /*
    auto a = CharaSlime::createNew();
    a->x = 37;
    a->y = 5;
    a->renewPosition();

    a->ally = AllyType::ally;

    */
    
    
    //消息循环
    while (!GlobalData::quitFlag)
    {
        //时间系统
        GlobalData::deltaTime = SDL_GetTicks() - GlobalData::lastTicks;
        GlobalData::lastTicks = SDL_GetTicks();
        GlobalData::FPS += 1;
        GlobalData::perSecondCountDown += GlobalData::deltaTime;
        if (GlobalData::perSecondCountDown >= 1000) {
#ifdef SHOW_FPS
            std::cout << "FPS:" << GlobalData::FPS << std::endl;
#endif // SHOW_FPS
            GlobalData::perSecondCountDown -= 1000;
            GlobalData::FPS = 0;
        }
        //物理帧时间累积
        GlobalData::logicFrameCD += GlobalData::deltaTime;

        //输入系统出力所有事件
        inputSystem->handleEvent();

        //控制窗口运动
        if (inputSystem->keydown_a) {
            worldSystem-> animSys->vx = -MAX_VIEW_SPEED_X;
        }
        if (inputSystem->keydown_d) {
            worldSystem-> animSys->vx = MAX_VIEW_SPEED_X;
        }
        if (inputSystem->keydown_w) {
            worldSystem-> animSys->vy = -MAX_VIEW_SPEED_Y;
        }
        if (inputSystem->keydown_s) {
            worldSystem-> animSys->vy = +MAX_VIEW_SPEED_Y;
        }
        if (inputSystem->keydown_x) {
            worldSystem-> animSys->vs = -MAX_VIEW_SPEED_SCALE;
        }
        if (inputSystem->keydown_c) {
            worldSystem-> animSys->vs = MAX_VIEW_SPEED_SCALE;
        }
        worldSystem-> animSys->updateWindow();

        //每16ms运行一次逻辑帧
        while (GlobalData::logicFrameCD > 16)
        {
            GlobalData::logicFrameCD -= 16;
            
            worldSystem->logicGo();
            //std::cout << a->form.health << "\n";
        }
        //渲染系统
        //渲染背景颜色
        SDL_SetRenderDrawColor(GlobalData::renderer, 14, 80, 81, 255);
        SDL_RenderClear(GlobalData::renderer);

        //渲染内容
        worldSystem-> animSys->renderAll();

        //交换双缓冲
        SDL_RenderPresent(GlobalData::renderer);
    }

    //结束清理
    
    std::cout << "\n--\t--\t--\t--结束清理--\t--\t--\t--\n\n";

    //释放创建的所有SDL stuff
    if (GlobalData::win) {
        SDL_DestroyWindow(GlobalData::win);
    }
    if (GlobalData::renderer) {
        SDL_DestroyRenderer(GlobalData::renderer);
    }

    inputSystem->destroyInstance();
    worldSystem->destroyInstance();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
