#include "idea_UI_scope.h"

#include "Defined.h"
#include "GameToolkit.h"
#include "GlobalData.h"
#include "UISystem.h"
#include "RenderingSystem.h"

idea_UI_scope* idea_UI_scope::createNew()
{
	return new idea_UI_scope();
}

void idea_UI_scope::updateOnRendering()
{
	renew_state();
	renew_texture();
}


idea_UI_scope::idea_UI_scope()
{

	color_r = 255;
	color_g = 255;
	color_b = 255;
	color_a = 255;

	name = L"UI_scope";

	rendering_unit = RenderingUnit::createNew();

	rendering_unit->deltaX = 0;
	rendering_unit->deltaY = 0;

	rendering_unit->reference = RenderingReference::window;

	rendering_unit->depth = DEPTH_FIXED_UI - 1;

	create_texture();
}

idea_UI_scope::~idea_UI_scope()
{
	destroy_texture();
}

void idea_UI_scope::enable()
{
	flag_static = true;
	rendering_unit->flag_enable = true;
}

void idea_UI_scope::disable()
{
	flag_static = false;
	rendering_unit->flag_enable = false;
}

void idea_UI_scope::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color_a = a;
	color_b = b;
	color_g = g;
	color_r = r;
}

void idea_UI_scope::renew_state()const
{
	const int _x = static_cast<int>(floor(UISystem::getInstance()->mouseX_world));
	const int _y = static_cast<int>(floor(UISystem::getInstance()->mouseY_world));

	rendering_unit->width = static_cast<int>(floor(RenderingSystem::getInstance()->viewScale * 32));
	rendering_unit->height = rendering_unit->width;

	GameToolkit::transPositionWorldToWindow(_x, _y,
		&rendering_unit->x, &rendering_unit->y);
}


void idea_UI_scope::create_texture()const
{
	SDL_Texture* texture = SDL_CreateTexture(GlobalData::sdl_renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		static_cast<int>(rendering_unit->width), static_cast<int>(rendering_unit->height));


	SDL_SetRenderTarget(GlobalData::sdl_renderer, texture);
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, color_r, color_g, color_b, color_a);
	SDL_RenderDrawRect(GlobalData::sdl_renderer, nullptr);

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	rendering_unit->setTexture(texture);
}

void idea_UI_scope::renew_texture()const
{
	destroy_texture();
	create_texture();
}


void idea_UI_scope::destroy_texture()const
{
	if (rendering_unit->getTexture())
	{
		SDL_DestroyTexture(rendering_unit->getTexture());
		rendering_unit->setTexture(nullptr);
	}
}
