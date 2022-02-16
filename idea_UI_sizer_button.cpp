#include "idea_UI_sizer_button.h"
#include "idea_UI_sizer.h"
#include "abstract_SizerTarget.h"
#include "Defined.h"
#include "GlobalData.h"
#include "RenderingSystem.h"

idea_UI_sizer_button* idea_UI_sizer_button::createNew()
{
	return new idea_UI_sizer_button();
}

idea_UI_sizer_button::idea_UI_sizer_button()
{
	name = L"ui_sizer_button";

	flag_static = true;
	flag_collider_enabled = true;

	update_depth(2);

	texture_default_ = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_grid_default, 0);
	texture_highlight_ = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_grid_highlight, 0);
	texture_pressed_ = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_grid_pressed, 0);

	current_texture_ = texture_default_;

	position_offset = 0;
	parent = nullptr;
	target = nullptr;
}

idea_UI_sizer_button::~idea_UI_sizer_button()
{
	destroyTexture();
}

void idea_UI_sizer_button::updateOnRendering()
{
	//更新材质

	destroyTexture();
	createTexture();

	//剪裁
	{
		const int raw_x = parent->collider_x;
		int raw_y = static_cast<int>(parent->collider_y + parent->position + round(position_offset));
		constexpr int raw_w = static_cast<int>(UI_SCALE) * 18;
		int raw_h = raw_w;

		if (raw_y < parent->collider_y)
		{
			const auto delta = parent->collider_y - raw_y;
			raw_y += delta;
			raw_h -= delta;
			if (raw_h <= 0)rendering_unit->flag_enable = false;
			else rendering_unit->flag_enable = true;
			setPosition(raw_x, raw_y, raw_w, raw_h);
			rendering_unit->setClipping(0, delta, raw_w, raw_h);
		}
		else if (raw_y + raw_h > parent->collider_y + parent->collider_h)
		{
			const auto delta = raw_y + raw_h - parent->collider_y - parent->collider_h;
			raw_h -= delta;
			if (raw_h <= 0)rendering_unit->flag_enable = false;
			else rendering_unit->flag_enable = true;
			setPosition(raw_x, raw_y, raw_w, raw_h);
			rendering_unit->setClipping(0, 0, raw_w, raw_h);
		}
		else
		{
			setPosition(raw_x, raw_y, raw_w, raw_h);

			if(rendering_unit->clipping_rect)
			{
				delete rendering_unit->clipping_rect;
				rendering_unit->clipping_rect = nullptr;
			}
		}
	}
}


void idea_UI_sizer_button::createTexture() const
{
#ifdef _DEBUG
	if (target == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"筛选器按钮没有设定目标");
	}
#endif

	const auto tar_thumbnail = target->getThumbnail();

#ifdef _DEBUG
	if(tar_thumbnail==nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"筛选器无法获取目标材质");
	}
#endif

	const auto texture = SDL_CreateTexture(GlobalData::sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,
		18 * static_cast<int>(UI_SCALE), 18 * static_cast<int>(UI_SCALE));
	
	SDL_SetRenderTarget(GlobalData::sdl_renderer, texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	constexpr SDL_Rect dst_rect = { static_cast<int>(UI_SCALE),static_cast<int>(UI_SCALE),
		static_cast<int>(UI_SCALE) * 16,static_cast<int>(UI_SCALE) * 16 };

	SDL_RenderCopy(GlobalData::sdl_renderer, current_texture_, nullptr, nullptr);
	SDL_RenderCopy(GlobalData::sdl_renderer, tar_thumbnail, nullptr, &dst_rect);

	rendering_unit->setTexture(texture);
}

void idea_UI_sizer_button::destroyTexture()const
{
	if(rendering_unit->getTexture())
	{
		SDL_DestroyTexture(rendering_unit->getTexture());
	}
}

void idea_UI_sizer_button::onMouseUp()
{
	UIObject::onMouseUp();
	SDL_Log(u8"设置目标");
	current_texture_ = texture_highlight_;
}

void idea_UI_sizer_button::onMousePressing()
{
	UIObject::onMousePressing();
	current_texture_ = texture_pressed_;
}

void idea_UI_sizer_button::onMouseEnter()
{
	UIObject::onMouseEnter();
	current_texture_ = texture_highlight_;
}

void idea_UI_sizer_button::onMouseExit()
{
	UIObject::onMouseExit();
	current_texture_ = texture_default_;
}


void idea_UI_sizer_button::onMouseRoll(bool forward)
{
	parent->onMouseRoll(forward);
}

void idea_UI_sizer_button::setup(idea_UI_sizer* _parent, abstract_SizerTarget* _target, int _offset)
{
	parent = _parent;
	target = _target;
	position_offset = _offset;

	createTexture();

	flag_static = false;
}
