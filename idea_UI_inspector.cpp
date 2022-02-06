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

	animation_unit = RenderingUnit::createNew();
	animation_unit->deltaX = 0;
	animation_unit->deltaY = 0;
	animation_unit->width = 0;
	animation_unit->height = 0;
	animation_unit->reference = RenderingReference::window;

	animation_unit->depth = RENDERING_DEPTH_UI+1;

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

	animation_unit->setTexture(texture);
	animation_unit->width = _width;
	animation_unit->height = _height;
}

void idea_UI_inspector::renew_texture() const
{
	//指定为渲染目标
	SDL_SetRenderTarget(GlobalData::sdl_renderer, animation_unit->getTexture());
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);

	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 204, 204, 204, 255);
	SDL_Rect rect={0,0,static_cast<int>(animation_unit->width),44};
	SDL_RenderFillRect(GlobalData::sdl_renderer, &rect);

	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 255, 255, 255, 255);
	rect = { 0,44,static_cast<int>(animation_unit->width),static_cast<int>(animation_unit->height) };
	SDL_RenderFillRect(GlobalData::sdl_renderer, &rect);

	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 106, 106, 106, 255);
	rect = { 4,48,static_cast<int>(animation_unit->width) - 8,static_cast<int>(animation_unit->height) - 52 };
	SDL_RenderFillRect(GlobalData::sdl_renderer, &rect);

	rect = { static_cast<int>(animation_unit->width) - 40,4,36,36 };
	SDL_RenderCopy(GlobalData::sdl_renderer, texture_exit_button, nullptr, &rect);

	animation_unit->x = WINDOW_WIDTH - animation_unit->width - 24;
	animation_unit->y = WINDOW_HEIGHT - animation_unit->height - 24;
}

void idea_UI_inspector::destroy_texture() const
{
	//手动销毁材质
	if (animation_unit->getTexture())
	{
		SDL_DestroyTexture(animation_unit->getTexture());
		animation_unit->setTexture(nullptr);
	}
}

void idea_UI_inspector::renew_state()
{
	const int _x1 = static_cast<int>(animation_unit->x + animation_unit->width) - 40;
	const int _y1 = static_cast<int>(animation_unit->y) + 4;
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
	animation_unit->flag_enable = true;
}

void idea_UI_inspector::disable()
{
	flag_enable = false;
	animation_unit->flag_enable = false;
}

