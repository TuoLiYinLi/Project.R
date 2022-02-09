#include "idea_UI_speed_controller.h"
#include "Defined.h"
#include "GlobalData.h"
#include "RenderingSystem.h"

idea_UI_speed_controller* idea_UI_speed_controller::createNew()
{
	return new idea_UI_speed_controller();
}

void idea_UI_speed_controller::updateOnRendering()
{
	if(GlobalData::flag_stop)
	{
		if (!b1->checkMouseIn())b1->rendering_unit->setTexture(texture_selected);
		if (!b2->checkMouseIn())b2->rendering_unit->setTexture(texture_default);
	}else
	{
		if (!b1->checkMouseIn())b1->rendering_unit->setTexture(texture_default);
		if (!b2->checkMouseIn())b2->rendering_unit->setTexture(texture_selected);
	}

	switch (GlobalData::getTimeSpeed())
	{
	case TimeSpeedType::normal:
		if (!b3->checkMouseIn())b3->rendering_unit->setTexture(texture_selected);
		if (!b4->checkMouseIn())b4->rendering_unit->setTexture(texture_default);
		if (!b5->checkMouseIn())b5->rendering_unit->setTexture(texture_default);
		break;

	case TimeSpeedType::double_speed:
		if (!b3->checkMouseIn())b3->rendering_unit->setTexture(texture_default);
		if (!b4->checkMouseIn())b4->rendering_unit->setTexture(texture_selected);
		if (!b5->checkMouseIn())b5->rendering_unit->setTexture(texture_default);
		break;

	case TimeSpeedType::triple_speed:
		if (!b3->checkMouseIn())b3->rendering_unit->setTexture(texture_default);
		if (!b4->checkMouseIn())b4->rendering_unit->setTexture(texture_default);
		if (!b5->checkMouseIn())b5->rendering_unit->setTexture(texture_selected);
		break;
	}
}


idea_UI_speed_controller::idea_UI_speed_controller()
{
	flag_collider_enabled = false;
	flag_static = false;

	rendering_unit->setTexture(RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_controller_mask, 0));
	rendering_unit->width = 37 * UI_SCALE;
	rendering_unit->height = 9 * UI_SCALE;
	rendering_unit->x = static_cast<double>(WINDOW_WIDTH) - rendering_unit->width - 10 * UI_SCALE - 16;
	rendering_unit->y = 16;
	update_depth(1);

	texture_default = SDL_CreateTexture(GlobalData::sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 7, 7);
	SDL_SetRenderTarget(GlobalData::sdl_renderer, texture_default);
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 204, 204, 204, 255);
	SDL_RenderFillRect(GlobalData::sdl_renderer, nullptr);

	texture_selected = SDL_CreateTexture(GlobalData::sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 7, 7);
	SDL_SetRenderTarget(GlobalData::sdl_renderer, texture_selected);
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 106, 106, 106, 106);
	SDL_RenderFillRect(GlobalData::sdl_renderer, nullptr);

	texture_highlight = SDL_CreateTexture(GlobalData::sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 7, 7);
	SDL_SetRenderTarget(GlobalData::sdl_renderer, texture_highlight);
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 251, 242, 54, 255);
	SDL_RenderFillRect(GlobalData::sdl_renderer, nullptr);

	texture_pressed = SDL_CreateTexture(GlobalData::sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 7, 7);
	SDL_SetRenderTarget(GlobalData::sdl_renderer, texture_pressed);
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 172, 50, 50, 255);
	SDL_RenderFillRect(GlobalData::sdl_renderer, nullptr);

	b1 = UIButton::createNew();
	b1->setPosition(
		static_cast<int>(rendering_unit->x + UI_SCALE),
		static_cast<int>(rendering_unit->y + UI_SCALE),
		static_cast<int>(7 * UI_SCALE),
		static_cast<int>(7 * UI_SCALE));
	b1->setCallback(set_time_stop);

	b1->texture_default = texture_default;
	b1->texture_pressed = texture_pressed;
	b1->texture_highlight = texture_highlight;

	b2 = UIButton::createNew();
	b2->setPosition(
		static_cast<int>(b1->rendering_unit->x + 7 * UI_SCALE),
		static_cast<int>(rendering_unit->y + UI_SCALE),
		static_cast<int>(7 * UI_SCALE),
		static_cast<int>(7 * UI_SCALE));
	b2->setCallback(set_time_go);

	b2->texture_default = texture_default;
	b2->texture_pressed = texture_pressed;
	b2->texture_highlight = texture_highlight;

	b3 = UIButton::createNew();
	b3->setPosition(
		static_cast<int>(b2->rendering_unit->x + 7 * UI_SCALE),
		static_cast<int>(rendering_unit->y + UI_SCALE),
		static_cast<int>(7 * UI_SCALE),
		static_cast<int>(7 * UI_SCALE));
	b3->setCallback(set_time_speed_1);

	b3->texture_default = texture_default;
	b3->texture_pressed = texture_pressed;
	b3->texture_highlight = texture_highlight;

	b4 = UIButton::createNew();
	b4->setPosition(
		static_cast<int>(b3->rendering_unit->x + 7 * UI_SCALE),
		static_cast<int>(rendering_unit->y + UI_SCALE),
		static_cast<int>(7 * UI_SCALE),
		static_cast<int>(7 * UI_SCALE));
	b4->setCallback(set_time_speed_2);

	b4->texture_default = texture_default;
	b4->texture_pressed = texture_pressed;
	b4->texture_highlight = texture_highlight;

	b5 = UIButton::createNew();
	b5->setPosition(
		static_cast<int>(b4->rendering_unit->x + 7 * UI_SCALE),
		static_cast<int>(rendering_unit->y + UI_SCALE),
		static_cast<int>(7 * UI_SCALE),
		static_cast<int>(7 * UI_SCALE));
	b5->setCallback(set_time_speed_3);

	b5->texture_default = texture_default;
	b5->texture_pressed = texture_pressed;
	b5->texture_highlight = texture_highlight;

	if (GlobalData::flag_stop)
	{
		b1->rendering_unit->setTexture(texture_selected);
		b2->rendering_unit->setTexture(texture_default);
	}
	else
	{

		b1->rendering_unit->setTexture(texture_default);
		b2->rendering_unit->setTexture(texture_selected);
	}

	switch (GlobalData::getTimeSpeed())
	{
	case TimeSpeedType::normal:

		b3->rendering_unit->setTexture(texture_selected);
		b4->rendering_unit->setTexture(texture_default);
		b5->rendering_unit->setTexture(texture_default);
		break;

	case TimeSpeedType::double_speed:
		b3->rendering_unit->setTexture(texture_default);
		b4->rendering_unit->setTexture(texture_selected);
		b5->rendering_unit->setTexture(texture_default);
		break;

	case TimeSpeedType::triple_speed:
		b3->rendering_unit->setTexture(texture_default);
		b4->rendering_unit->setTexture(texture_default);
		b5->rendering_unit->setTexture(texture_selected);
		break;
	}
}

idea_UI_speed_controller::~idea_UI_speed_controller()
{
	SDL_DestroyTexture(texture_default);
	SDL_DestroyTexture(texture_selected);
	SDL_DestroyTexture(texture_pressed);
	SDL_DestroyTexture(texture_highlight);
}

void idea_UI_speed_controller::set_time_go()
{
	GlobalData::flag_stop = false;
}

void idea_UI_speed_controller::set_time_stop()
{
	GlobalData::flag_stop = true;
}

void idea_UI_speed_controller::set_time_speed_1()
{
	GlobalData::setTimeSpeed(TimeSpeedType::normal);
}

void idea_UI_speed_controller::set_time_speed_2()
{
	GlobalData::setTimeSpeed(TimeSpeedType::double_speed);
}

void idea_UI_speed_controller::set_time_speed_3()
{
	GlobalData::setTimeSpeed(TimeSpeedType::triple_speed);
}


