#include "UIScroll.h"

#include "GlobalData.h"

UIScroll* UIScroll::createNew()
{
	return new UIScroll();
}

UIScroll::UIScroll()
{
	name = L"default_ui_scroll";

	flag_static = true;
	flag_collider_enabled = false;
	rendering_unit->flag_enable = false;

	texture_full = nullptr;
	texture_full_height = 100;
	texture_full_width = 100;

	position = 0;
	velocity = 0;
	limit_length = 0;
	obstruction = 0;
	resistance = 0.5;
	mouse_roll_speed = 25;
	user_rolling = false;

	reset_color_a = 10;
	reset_color_b = 255;
	reset_color_r = 255;
	reset_color_g = 255;

	can_destroy_texture = false;
}

UIScroll::~UIScroll()
{
	if (rendering_unit->getTexture())
	{
		SDL_DestroyTexture(rendering_unit->getTexture());
	}
	if (texture_full)SDL_DestroyTexture(texture_full);
}

void UIScroll::updateOnRendering()
{
	UIObject::updateOnRendering();

	//更新位置
	position += velocity * GlobalData::getTimeDelta() / 1000;

	if (texture_full_height > rendering_unit->height)
	{
		//当材质超出区域时
		
		//可以运动的长度空间
		const auto available_length = texture_full_height - rendering_unit->height;

		//限制
		if (position < -limit_length)
		{
			position = -limit_length;
			if (!user_rolling)velocity = limit_length * resistance;
		}
		else if (position < 0)
		{
			if (!user_rolling)velocity = -position * resistance;
		}
		else if (position <= available_length)
		{
			if (velocity > 0)
			{
				if (velocity > obstruction)velocity -= obstruction;
				else velocity = 0;
			}
			else if (velocity < 0)
			{
				if (velocity < obstruction)velocity += obstruction;
				else velocity = 0;
			}
		}
		else if (position > available_length)
		{
			if (!user_rolling)velocity = (available_length - position) * resistance;
		}
		else if (position > available_length + limit_length)
		{
			position = available_length + limit_length;
			if (!user_rolling)velocity = -limit_length * resistance;
		}

	}
	else
	{
		//当区域比材质更长时
		if (position < -limit_length)
		{
			position = -limit_length;
			if (!user_rolling)velocity = limit_length * resistance;
		}
		else if (position < 0|| position > 0)
		{
			if (!user_rolling)velocity = -position * resistance;
		}
		else if (position > + limit_length)
		{
			position = + limit_length;
			if (!user_rolling)velocity = -limit_length * resistance;
		}
	}
	user_rolling = false;
	//更新材质
	destroy_texture();
	create_texture();
}

void UIScroll::onMouseRoll(bool forward)
{
	UIObject::onMouseRoll(forward);

	user_rolling = true;
	if(forward)
	{
		velocity += mouse_roll_speed;
	}else
	{
		velocity += -mouse_roll_speed;
	}
}

void UIScroll::setUp(SDL_Texture* _texture_full, int _x, int _y, int _texture_width, int _texture_height,int _display_height, double _limit_length, double _obstruction, double _resistant, double roll_speed)
{
	flag_static = false;
	flag_collider_enabled = true;
	rendering_unit->flag_enable = true;

	texture_full = _texture_full;
	SDL_SetTextureBlendMode(texture_full, SDL_BLENDMODE_NONE);
	texture_full_width = _texture_width;
	texture_full_height = _texture_height;
	limit_length = _limit_length;
	resistance = _resistant;
	obstruction = _obstruction;
	mouse_roll_speed = roll_speed;

	setPosition(_x, _y, _texture_width, _display_height);
}

void UIScroll::create_texture()
{
	const auto t = SDL_CreateTexture(GlobalData::sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, rendering_unit->width, rendering_unit->height);
	SDL_SetRenderTarget(GlobalData::sdl_renderer, t);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);

	//材质绘制
	if (texture_full_height > rendering_unit->height)
	{
		//当材质超出区域时
		if (position + rendering_unit->height > texture_full_height)
		{
			//区域到材质下方
			SDL_SetRenderDrawColor(GlobalData::sdl_renderer, reset_color_r, reset_color_g, reset_color_b, reset_color_a);
			SDL_RenderClear(GlobalData::sdl_renderer);
			const SDL_Rect src = {
				0,
				static_cast<int>(position),
				texture_full_width,
				static_cast<int>(texture_full_height - position) };
			const SDL_Rect dst = {
				0,
				0,
				texture_full_width,
				static_cast<int>(ceil(texture_full_height - position)) };
			SDL_RenderCopy(GlobalData::sdl_renderer, texture_full, &src, &dst);
		}
		else if (position < 0)
		{
			//区域在材质上方
			SDL_SetRenderDrawColor(GlobalData::sdl_renderer, reset_color_r, reset_color_g, reset_color_b, reset_color_a);
			SDL_RenderClear(GlobalData::sdl_renderer);
			const SDL_Rect src = {
				0,
				static_cast<int>(position),
				texture_full_width,
				static_cast<int>(rendering_unit->height) };
			const SDL_Rect dst = {
				0,
				-static_cast<int>(position),
				texture_full_width,
				static_cast<int>(ceil(rendering_unit->height + position)) };
			SDL_RenderCopy(GlobalData::sdl_renderer, texture_full, &src, &dst);
		}
		else
		{
			//区域在材质中部
			const SDL_Rect src = {
				0,
				static_cast<int>(position),
				texture_full_width,
				static_cast<int>(rendering_unit->height) };
			SDL_RenderCopy(GlobalData::sdl_renderer, texture_full, &src, nullptr);
		}

	}
	else
	{
		//当区域比材质更长时

		SDL_SetRenderDrawColor(GlobalData::sdl_renderer, reset_color_r, reset_color_g, reset_color_b, reset_color_a);
		SDL_RenderClear(GlobalData::sdl_renderer);
		if (position > 0)
		{
			//材质到区域的上部
			const SDL_Rect dst = {
				0,
				0,
				texture_full_width,
				texture_full_height - static_cast<int>(position) };
			const SDL_Rect src = {
				0,
				static_cast<int>(position),
				texture_full_width,
				texture_full_height - static_cast<int>(position) };
			SDL_RenderCopy(GlobalData::sdl_renderer, texture_full, &src, &dst);

		}
		else if (texture_full_height > rendering_unit->height + position)
		{
			//材质到区域的下侧
			const SDL_Rect dst = {
				0,
				-static_cast<int>(position),
				texture_full_width,
				static_cast<int>(rendering_unit->height + position) };
			const SDL_Rect src = {
				0,
				0,
				texture_full_width,
				static_cast<int>(rendering_unit->height + position) };
			SDL_RenderCopy(GlobalData::sdl_renderer, texture_full, &src, &dst);

		}
		else
		{
			//材质在区域中间
			const SDL_Rect dst = {
				0,
				-static_cast<int>(position),
				texture_full_width,
				texture_full_height };
			SDL_RenderCopy(GlobalData::sdl_renderer, texture_full, nullptr, &dst);
		}
	}

	rendering_unit->setTexture(t);
	can_destroy_texture = true;
}

void UIScroll::destroy_texture()
{
	if (can_destroy_texture)
	{
		SDL_DestroyTexture(rendering_unit->getTexture());
		can_destroy_texture = false;
	}
}


