#include "idea_debugger_physics.h"
#include "GlobalData.h"
#include "Defined.h"
#include "GameToolkit.h"
#include "PhysicsFacility.h"
#include "PhysicsChara.h"
#include "PhysicsProjectile.h"
#include "RenderingSystem.h"
#include "WorldSystem.h"

idea_debugger_physics* idea_debugger_physics::createNew()
{
	return new idea_debugger_physics();
}

void idea_debugger_physics::updateOnRendering()
{
    if (GlobalData::flag_debug_physics)
    {
		renew_texture();
        animation_unit->flag_enable=true;
    }else
    {
        animation_unit->flag_enable = false;
    }
}

void idea_debugger_physics::renew_texture()const
{
    //指定为渲染目标，开始调整
    SDL_SetRenderTarget(GlobalData::sdl_renderer, animation_unit->getTexture());
    //渲染为完全透明
    SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 0, 0, 0, 0);
    SDL_RenderClear(GlobalData::sdl_renderer);
    //渲染物理体
    render_all_grids();
}

void idea_debugger_physics::create_texture()const
{
    //创建纹理
    SDL_Texture* texture = SDL_CreateTexture(GlobalData::sdl_renderer,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        WINDOW_WIDTH, WINDOW_HEIGHT);

    animation_unit->setTexture(texture);
    SDL_SetTextureAlphaMod(animation_unit->getTexture(),160);
    SDL_SetTextureBlendMode(animation_unit->getTexture(), SDL_BLENDMODE_BLEND);
}

void idea_debugger_physics::destroy_texture()const
{
    //手动销毁材质
    if (animation_unit->getTexture())
    {
        SDL_DestroyTexture(animation_unit->getTexture());
        animation_unit->setTexture(nullptr);
    }
}




void idea_debugger_physics::render_one_grid(int grid_x, int grid_y)const
{
    SDL_SetRenderTarget(GlobalData::sdl_renderer, animation_unit->getTexture());

    double x_tar, y_tar;
    GameToolkit::transPositionWorldToWindow(grid_x, grid_y, &x_tar, &y_tar);
    const int w = static_cast<int>(floor(RenderingSystem::getInstance()->viewScale * 32));
    const int h = w;
    const SDL_Rect rect = { static_cast<int>(floor(x_tar)),static_cast<int>(floor(y_tar)),w,h };

    Grid* g = WorldSystem::getInstance()->getGrid(grid_x, grid_y);
    if(g!=nullptr)
    {
	    if(!g->list_physics_chara->empty())
	    {
            SDL_RenderCopy(GlobalData::sdl_renderer, 
                RenderingSystem::getInstance()->getAnimation(AnimationType::debug_physics_chara, 0), 
                nullptr, &rect);
	    }
	    if (g->getBlockingType(BlockingType::support))
	    {
            SDL_RenderCopy(GlobalData::sdl_renderer,
                RenderingSystem::getInstance()->getAnimation(AnimationType::debug_physics_support, 0),
                nullptr, &rect);
	    }
	    if(g->getBlockingType(BlockingType::air))
	    {
            SDL_RenderCopy(GlobalData::sdl_renderer,
                RenderingSystem::getInstance()->getAnimation(AnimationType::debug_physics_air, 0),
                nullptr, &rect);
	    }
		if (g->getBlockingType(BlockingType::liquid))
	    {
            SDL_RenderCopy(GlobalData::sdl_renderer,
                RenderingSystem::getInstance()->getAnimation(AnimationType::debug_physics_liquid, 0),
                nullptr, &rect);
	    }
	    if (!g->list_physics_projectile->empty())
	    {
            SDL_RenderCopy(GlobalData::sdl_renderer,
                RenderingSystem::getInstance()->getAnimation(AnimationType::debug_physics_projectile, 0),
                nullptr, &rect);
	    }
	    if (g->getBlockingType(BlockingType::solid))
	    {
            SDL_RenderCopy(GlobalData::sdl_renderer,
                RenderingSystem::getInstance()->getAnimation(AnimationType::debug_physics_solid, 0),
                nullptr, &rect);
	    }
    }else
    {
	    //在外部
        SDL_RenderCopy(GlobalData::sdl_renderer,
            RenderingSystem::getInstance()->getAnimation(AnimationType::debug_physics_outside, 0),
            nullptr, &rect);
    }

}

void idea_debugger_physics::render_all_grids()const
{
    double x_start, y_start, x_end, y_end;
    GameToolkit::transPositionWindowToWorld(0, 0, &x_start, &y_start);
    GameToolkit::transPositionWindowToWorld(WINDOW_WIDTH, WINDOW_HEIGHT, &x_end, &y_end);

    for (int i = static_cast<int>(floor(x_start)); i < x_end; ++i)
    {
        for (int j = static_cast<int>(floor(y_start)); j < y_end; ++j)
        {
            render_one_grid(i, j);
        }
    }
}



idea_debugger_physics::idea_debugger_physics()
{
    name = "physics_debugger";

	animation_unit = RenderingUnit::createNew();
    animation_unit->deltaX = 0;
    animation_unit->deltaY = 0;
    animation_unit->width = WINDOW_WIDTH;
    animation_unit->height = WINDOW_HEIGHT;
    animation_unit->reference = RenderingReference::window;
    animation_unit->depth = RENDERING_DEPTH_EXTRA + 1;
    create_texture();
    renew_texture();
}

idea_debugger_physics::~idea_debugger_physics()
{
    destroy_texture();
}