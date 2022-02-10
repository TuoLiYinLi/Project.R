#include "idea_UI_energy.h"

#include "Defined.h"
#include "GlobalData.h"
#include "RenderingSystem.h"
#include "WorldSystem.h"

idea_UI_energy* idea_UI_energy::createNew()
{
	return new idea_UI_energy();
}

idea_UI_energy::idea_UI_energy()
{
	flag_static = false;
	rendering_unit->setTexture(RenderingSystem::getInstance()->getAnimation(AnimationType::ui_energy_bar, 0));
	update_depth(0);
	setPosition(
		6 * static_cast<int>(UI_SCALE),
		6 * static_cast<int>(UI_SCALE),
		102 * static_cast<int>(UI_SCALE),
		4 * static_cast<int>(UI_SCALE));

	inside_image = RenderingUnit::createNew();
	inside_image->depth = rendering_unit->depth + 1;
	inside_image->reference = RenderingReference::window;
	inside_image->x = rendering_unit->x + UI_SCALE;
	inside_image->y = rendering_unit->y + UI_SCALE;
	inside_image->width = UI_SCALE * 100;
	inside_image->height = UI_SCALE * 2;

	create_texture();
	renew_texture();
}

idea_UI_energy::~idea_UI_energy()
{
	destroy_texture();
	inside_image->destroy();
}

void idea_UI_energy::updateOnRendering()
{
	renew_texture();
}


void idea_UI_energy::create_texture()const
{
	const auto t = SDL_CreateTexture(GlobalData::sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 
		static_cast<int>(UI_SCALE) * 100, static_cast<int>(UI_SCALE) * 2);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	inside_image->setTexture(t);
}

void idea_UI_energy::renew_texture()const
{
	SDL_SetRenderTarget(GlobalData::sdl_renderer, inside_image->getTexture());
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 255, 255, 255, 0);
	SDL_RenderClear(GlobalData::sdl_renderer);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 255, 200, 0, 255);
	const int goldust_energy_length = static_cast<int>(round(WorldSystem::getInstance()->goldust_energy / WorldSystem::getInstance()->goldust_goal * 100 * UI_SCALE));
	SDL_Rect r = {
		0,0,
		goldust_energy_length,
		static_cast<int>(UI_SCALE) * 2 };
	SDL_RenderFillRect(GlobalData::sdl_renderer, &r);
}

void idea_UI_energy::destroy_texture()const
{
	if(inside_image->getTexture())
	{
		SDL_DestroyTexture(inside_image->getTexture());
	}
}

