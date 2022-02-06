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
	if(!flag_enable)return;
	renew_state();
	destroy_texture();
	create_texture();
	renew_texture();
}


idea_UI_scope::idea_UI_scope()
{
	flag_enable = true;

	color_r = 255;
	color_g = 255;
	color_b = 255;
	color_a = 255;

	name = u8"UI_scope";

	animation_unit = RenderingUnit::createNew();

	animation_unit->deltaX = 0;
	animation_unit->deltaY = 0;

	animation_unit->reference = RenderingReference::window;

	animation_unit->depth = RENDERING_DEPTH_UI;
}

idea_UI_scope::~idea_UI_scope()
{
	destroy_texture();
}

void idea_UI_scope::enable()
{
	flag_enable = true;
	animation_unit->flag_enable = true;
}

void idea_UI_scope::disable()
{
	flag_enable = false;
	animation_unit->flag_enable = false;
}

void idea_UI_scope::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color_a = a;
	color_b = b;
	color_g = g;
	color_r = r;
}

void idea_UI_scope::renew_state()
{
	const int _x = static_cast<int>(floor(UISystem::getInstance()->mouseX_world));
	const int _y = static_cast<int>(floor(UISystem::getInstance()->mouseY_world));

	animation_unit->width = static_cast<int>(floor(RenderingSystem::getInstance()->viewScale * 32));
	animation_unit->height = animation_unit->width;

	GameToolkit::transPositionWorldToWindow(_x, _y,
		&animation_unit->x, &animation_unit->y);
}


void idea_UI_scope::create_texture()
{
	SDL_Texture* texture = SDL_CreateTexture(GlobalData::sdl_renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		static_cast<int>(animation_unit->width), static_cast<int>(animation_unit->height));
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	animation_unit->setTexture(texture);
}

void idea_UI_scope::renew_texture()
{
	SDL_SetRenderTarget(GlobalData::sdl_renderer, animation_unit->getTexture());
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, color_r, color_g, color_b, color_a);
	SDL_RenderDrawRect(GlobalData::sdl_renderer, nullptr);
}


void idea_UI_scope::destroy_texture()
{
	if (animation_unit->getTexture())
	{
		SDL_DestroyTexture(animation_unit->getTexture());
		animation_unit->setTexture(nullptr);
	}
}
