#include "idea_UI_sizer_button.h"
#include "idea_UI_sizer.h"
#include "abstract_inspect_target.h"
#include "Defined.h"
#include "GlobalData.h"
#include "RenderingSystem.h"
#include "RenderingText.h"
#include "UISystem.h"
#include "idea_UI_inspector.h"

idea_UI_sizer_button* idea_UI_sizer_button::createNew()
{
	return new idea_UI_sizer_button();
}

idea_UI_sizer_button::idea_UI_sizer_button()
{
	name = L"筛选器按钮";

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

	floating_text = nullptr;

	can_destroy_texture = false;
}

idea_UI_sizer_button::~idea_UI_sizer_button()
{
	destroyTexture();
	destroy_floating_text();
}

void idea_UI_sizer_button::updateOnRendering()
{
	//更新材质
	destroyTexture();
	if(target)
	{
		createTexture();
	}
	else
	{
		rendering_unit->setTexture(RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_grid_banned,0));
	}

	//剪裁
	{
		const int raw_x = parent->collider_x;
		int raw_y = static_cast<int>(parent->collider_y + parent->position + round(position_offset));
		constexpr int raw_w = static_cast<int>(ui_scale) * 18;
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

	renew_floating_text_position();
}


void idea_UI_sizer_button::createTexture()
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
		18 * static_cast<int>(ui_scale), 18 * static_cast<int>(ui_scale));
	
	SDL_SetRenderTarget(GlobalData::sdl_renderer, texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	constexpr SDL_Rect dst_rect = { static_cast<int>(ui_scale),static_cast<int>(ui_scale),
		static_cast<int>(ui_scale) * 16,static_cast<int>(ui_scale) * 16 };

	SDL_RenderCopy(GlobalData::sdl_renderer, current_texture_, nullptr, nullptr);
	SDL_RenderCopy(GlobalData::sdl_renderer, tar_thumbnail, nullptr, &dst_rect);

	rendering_unit->setTexture(texture);
	can_destroy_texture = true;
}

void idea_UI_sizer_button::destroyTexture()
{
	if(can_destroy_texture)
	{
		SDL_DestroyTexture(rendering_unit->getTexture());
		can_destroy_texture = false;
	}
}

void idea_UI_sizer_button::onMouseUp()
{
	UIObject::onMouseUp();
	if(target)
	{
		GlobalData::ui_inspector->set_target(target);
		GlobalData::ui_inspector->enable();
		GlobalData::ui_sizer->disable();
	}
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
	create_floating_text();
}

void idea_UI_sizer_button::onMouseExit()
{
	UIObject::onMouseExit();
	current_texture_ = texture_default_;
	destroy_floating_text();
}


void idea_UI_sizer_button::onMouseRoll(bool forward)
{
	parent->onMouseRoll(forward);
}

void idea_UI_sizer_button::setup(idea_UI_sizer* _parent, abstract_inspect_target* _target, int _offset)
{
	parent = _parent;
	target = _target;
	_target->pointer_to_this_sizer_button = &target;
	position_offset = _offset;

	createTexture();

	flag_static = false;
}

void idea_UI_sizer_button::set_inspector()
{
	
}

void idea_UI_sizer_button::create_floating_text()
{
	if(!target)return;

	floating_text = RenderingText::createNew();
	floating_text->setTexture(target->getBrief().c_str(), 1, { 255,255,255,255 }, { 0,0,0,205 });

	floating_text->setClipping(0, 0, static_cast<int>(floating_text->width), static_cast<int>(floating_text->height)-8);
	floating_text->height -= 8;

	floating_text->x = static_cast<double>(UISystem::getInstance()->mouseX_window) + 16;
	floating_text->y = UISystem::getInstance()->mouseY_window - floating_text->height / 2;

	floating_text->reference = RenderingReference::window;
	floating_text->depth = depth_fixed_ui + 3;

}

void idea_UI_sizer_button::destroy_floating_text()
{
	if(floating_text)
	{
		floating_text->destroy();
		floating_text = nullptr;
	}
}

void idea_UI_sizer_button::renew_floating_text_position()const
{
	if (floating_text)
	{
		floating_text->x = static_cast<double>(UISystem::getInstance()->mouseX_window) + 16;
		floating_text->y = UISystem::getInstance()->mouseY_window - floating_text->height / 2;
	}
}
