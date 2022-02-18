#include "idea_UI_inspector.h"
#include "Defined.h"
#include "GameToolkit.h"
#include "RenderingSystem.h"
#include "abstract_inspect_target.h"
#include "idea_UI_inspector_exit.h"
#include "UIScroll.h"

idea_UI_inspector* idea_UI_inspector::createNew()
{
	return new idea_UI_inspector();
}

void idea_UI_inspector::updateOnRendering()
{
	if(!target)
	{
		disable();
		return;
	}

	{
		if (t_main)
		{
			SDL_DestroyTexture(t_main);
			t_main = nullptr;
		}
		int w, h;
		t_main = GameToolkit::createUnicodeText(target->getMainInfo().c_str(), { 255,255,255,255 }, 46 * static_cast<int>(UI_SCALE), &w, &h);
		s_main->setup(t_main, collider_x + 2 * static_cast<int>(UI_SCALE), collider_y + 10 * static_cast<int>(UI_SCALE), w, h, 70 * static_cast<int>(UI_SCALE),
			24, 50, 8, 500);
	}
	//更新中间的卷轴UI
	{
		if(t_data)
		{
			SDL_DestroyTexture(t_data);
			t_data = nullptr;
		}
		int w, h;
		t_data = GameToolkit::createUnicodeText(target->getDataInfo().c_str(), { 255,255,255,255 }, 46 * static_cast<int>(UI_SCALE), &w, &h);
		s_data->setup(t_data, collider_x + (2 + 49) * static_cast<int>(UI_SCALE), collider_y + 10 * static_cast<int>(UI_SCALE), w, h, 70 * static_cast<int>(UI_SCALE),
			24, 50, 8, 500);
	}

	{
		if (t_extra)
		{
			SDL_DestroyTexture(t_extra);
			t_extra = nullptr;
		}
		int w, h;
		t_extra = GameToolkit::createUnicodeText(target->getExtraInfo().c_str(), { 255,255,255,255 }, 46 * static_cast<int>(UI_SCALE), &w, &h);
		s_extra->setup(t_extra, collider_x + (2 + 98) * static_cast<int>(UI_SCALE), collider_y + 10 * static_cast<int>(UI_SCALE), w, h, 70 * static_cast<int>(UI_SCALE),
			24, 50, 8, 500);
	}
	
}

idea_UI_inspector::idea_UI_inspector()
{
	flag_enable = true;

	target = nullptr;

	name = L"检视器";
	
	rendering_unit->reference = RenderingReference::window;
	rendering_unit->setTexture(RenderingSystem::getInstance()->getAnimation(AnimationType::ui_inspector_panel, 0));

	setPosition(
		WINDOW_WIDTH - (4 + 148) * static_cast<int>(UI_SCALE),
		WINDOW_HEIGHT - (4 + 82) * static_cast<int>(UI_SCALE),
		148 * static_cast<int>(UI_SCALE),
		82 * static_cast<int>(UI_SCALE));

	rendering_unit->depth = DEPTH_FIXED_UI+1;

	exit_button = idea_UI_inspector_exit::createNew();
	exit_button->setPosition(
		WINDOW_WIDTH - (4 + 9) * static_cast<int>(UI_SCALE),
		WINDOW_HEIGHT - (4 + 82) * static_cast<int>(UI_SCALE),
		9 * static_cast<int>(UI_SCALE),
		9 * static_cast<int>(UI_SCALE));
	exit_button->update_depth(2);

	t_main = nullptr;
	t_data = nullptr;
	t_extra = nullptr;

	s_main = UIScroll::createNew();
	s_main->update_depth(2);

	s_data = UIScroll::createNew();
	s_data->update_depth(2);

	s_extra = UIScroll::createNew();
	s_extra->update_depth(2);

	disable();
}

idea_UI_inspector::~idea_UI_inspector()
{

}

void idea_UI_inspector::enable()
{
	flag_enable = true;
	flag_collider_enabled = true;
	flag_static = false;
	rendering_unit->flag_enable = true;

	exit_button->enable();

	s_main->enable();
	s_data->enable();
	s_extra->enable();
}

void idea_UI_inspector::disable()
{
	flag_enable = false;
	flag_collider_enabled = false;
	flag_static = true;
	rendering_unit->flag_enable = false;

	exit_button->disable();

	s_main->disable();
	s_data->disable();
	s_extra->disable();
}

void idea_UI_inspector::set_target(abstract_inspect_target* _target)
{
	target = _target;
	target->pointer_to_this_inspector = &target;
}
