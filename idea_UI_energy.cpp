#include "idea_UI_energy.h"

#include "Defined.h"
#include "GlobalData.h"
#include "RenderingSystem.h"
#include "WorldSystem.h"
#include "RenderingText.h"
#include "UISystem.h"

idea_UI_energy* idea_UI_energy::createNew()
{
	return new idea_UI_energy();
}

idea_UI_energy::idea_UI_energy()
{
	name = L"金沙能量条";

	flag_static = false;
	rendering_unit->setTexture(RenderingSystem::getInstance()->getAnimation(AnimationType::ui_energy_bar, 0));
	update_depth(0);
	setPosition(
		6 * static_cast<int>(ui_scale),
		6 * static_cast<int>(ui_scale),
		102 * static_cast<int>(ui_scale),
		4 * static_cast<int>(ui_scale));

	inside_image = RenderingUnit::createNew();
	inside_image->depth = rendering_unit->depth + 1;
	inside_image->reference = RenderingReference::window;
	inside_image->x = rendering_unit->x + ui_scale;
	inside_image->y = rendering_unit->y + ui_scale;
	inside_image->width = ui_scale * 100;
	inside_image->height = ui_scale * 2;

	create_texture();
	renew_texture();

	should_display_text = false;
	floating_text = nullptr;
}

idea_UI_energy::~idea_UI_energy()
{
	destroy_texture();
	inside_image->destroy();
}

void idea_UI_energy::updateOnRendering()
{
	renew_texture();
	//刷新文字
	if(should_display_text)
	{
		if(floating_text)
		{
			destroy_text();
		}
		create_text();
	}else
	{
		destroy_text();
	}
}


void idea_UI_energy::create_texture()const
{
	const auto t = SDL_CreateTexture(GlobalData::sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 
		static_cast<int>(ui_scale) * 100, static_cast<int>(ui_scale) * 2);
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
	const int goldust_energy_length = static_cast<int>(round(WorldSystem::getInstance()->goldust_energy / WorldSystem::getInstance()->goldust_goal * 100 * ui_scale));
	const SDL_Rect r = {
		0,0,
		goldust_energy_length,
		static_cast<int>(ui_scale) * 2 };
	SDL_RenderFillRect(GlobalData::sdl_renderer, &r);
}

void idea_UI_energy::destroy_texture()const
{
	if(inside_image->getTexture())
	{
		SDL_DestroyTexture(inside_image->getTexture());
	}
}

void idea_UI_energy::onMouseEnter()
{
	UIObject::onMouseEnter();
	should_display_text = true;
}

void idea_UI_energy::onMouseExit()
{
	UIObject::onMouseExit();
	should_display_text = false;
}

void idea_UI_energy::create_text()
{
	floating_text = RenderingText::createNew();

	const std::wstring msg = L"金沙能量 " + std::to_wstring(static_cast<int>(WorldSystem::getInstance()->goldust_energy)) + L'/' + std::to_wstring(static_cast<int>(WorldSystem::getInstance()->goldust_goal));
	floating_text->setTexture(msg.c_str(), 1, { 255,255,255,255 }, { 0,0,0,205 });

	floating_text->setClipping(0, 0, static_cast<int>(floating_text->width), static_cast<int>(floating_text->height) - 8);
	floating_text->height -= 8;

	floating_text->x = static_cast<double>(UISystem::getInstance()->mouseX_window) + 16;
	floating_text->y = UISystem::getInstance()->mouseY_window - floating_text->height / 2;

	floating_text->reference = RenderingReference::window;
	floating_text->depth = depth_fixed_ui + 3;
}

void idea_UI_energy::destroy_text()
{
	//销毁漂浮文字
	if (floating_text)
	{
		floating_text->destroy();
		floating_text = nullptr;
	}
}
