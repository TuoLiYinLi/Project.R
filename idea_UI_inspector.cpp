#include "idea_UI_inspector.h"
#include "Defined.h"
#include "GameToolkit.h"
#include "GlobalData.h"
#include "RenderingSystem.h"
#include "UISystem.h"

idea_UI_inspector* idea_UI_inspector::createNew()
{
	return new idea_UI_inspector();
}

void idea_UI_inspector::updateOnRendering()
{
	if (!flag_enable)return;

	renew_state();
	renew_texture();
}

idea_UI_inspector::idea_UI_inspector()
{
	texture_exit_button = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_default, 0);

	flag_enable = true;

	tar_monster = nullptr;
	tar_facility = nullptr;
	tar_warrior = nullptr;

	name = u8"UI_inspector";

	rendering_unit = RenderingUnit::createNew();
	rendering_unit->deltaX = 0;
	rendering_unit->deltaY = 0;
	rendering_unit->width = 0;
	rendering_unit->height = 0;
	rendering_unit->reference = RenderingReference::window;

	rendering_unit->depth = RENDERING_DEPTH_UI+1;

	create_texture(146, 77);
	renew_texture();
}

idea_UI_inspector::~idea_UI_inspector()
{
	destroy_texture();
}

void idea_UI_inspector::create_texture(int w,int h) const
{
	const int _width = w * 4;
	const int _height = h * 4 + 44;

	SDL_Texture* texture = SDL_CreateTexture(GlobalData::sdl_renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		_width, _height);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);

	rendering_unit->setTexture(texture);
	rendering_unit->width = _width;
	rendering_unit->height = _height;
}

void idea_UI_inspector::renew_texture() const
{
	//指定为渲染目标
	SDL_SetRenderTarget(GlobalData::sdl_renderer, rendering_unit->getTexture());
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);

	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 204, 204, 204, 255);
	SDL_Rect rect={0,0,static_cast<int>(rendering_unit->width),44};
	SDL_RenderFillRect(GlobalData::sdl_renderer, &rect);

	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 255, 255, 255, 255);
	rect = { 0,44,static_cast<int>(rendering_unit->width),static_cast<int>(rendering_unit->height) };
	SDL_RenderFillRect(GlobalData::sdl_renderer, &rect);

	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 106, 106, 106, 255);
	rect = { 4,48,static_cast<int>(rendering_unit->width) - 8,static_cast<int>(rendering_unit->height) - 52 };
	SDL_RenderFillRect(GlobalData::sdl_renderer, &rect);

	rect = { static_cast<int>(rendering_unit->width) - 40,4,36,36 };
	SDL_RenderCopy(GlobalData::sdl_renderer, texture_exit_button, nullptr, &rect);

	rendering_unit->x = WINDOW_WIDTH - rendering_unit->width - 24;
	rendering_unit->y = WINDOW_HEIGHT - rendering_unit->height - 24;
}

void idea_UI_inspector::destroy_texture() const
{
	//手动销毁材质
	if (rendering_unit->getTexture())
	{
		SDL_DestroyTexture(rendering_unit->getTexture());
		rendering_unit->setTexture(nullptr);
	}
}

void idea_UI_inspector::renew_state()
{
	const int _x1 = static_cast<int>(rendering_unit->x + rendering_unit->width) - 40;
	const int _y1 = static_cast<int>(rendering_unit->y) + 4;
	const int _x2 = _x1 + 36;
	const int _y2 = _y1 + 36;

	if (GameToolkit::checkMouseInRange(_x1,_y1,_x2,_y2))
	{
		if(UISystem::getInstance()->mouse_left_release)
		{
			disable();
		}

		if(UISystem::getInstance()->mouse_left_state)
		{
			texture_exit_button= RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_pressed, 0);
		}else
		{
			texture_exit_button = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_highlight, 0);
		}
	}else
	{
		texture_exit_button = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_default, 0);
	}
}

void idea_UI_inspector::enable()
{
	flag_enable = true;
	rendering_unit->flag_enable = true;
}

void idea_UI_inspector::disable()
{
	flag_enable = false;
	rendering_unit->flag_enable = false;
}

