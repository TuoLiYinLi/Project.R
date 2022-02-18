#include "idea_UI_button_menu.h"

#include "Defined.h"
#include "RenderingSystem.h"

idea_UI_button_menu* idea_UI_button_menu::createNew()
{
	return new idea_UI_button_menu();
}

idea_UI_button_menu::idea_UI_button_menu()
{
	name = L"²Ëµ¥°´Å¥";

	texture_default = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_menu_default, 0);
	texture_highlight = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_menu_highlight, 0);
	texture_pressed = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_menu_pressed, 0);
	rendering_unit->setTexture(texture_default);

	setPosition(WINDOW_WIDTH - 9 * static_cast<int>(ui_scale) - 16, 16,
		9 * static_cast<int>(ui_scale), 9 * static_cast<int>(ui_scale));
}

idea_UI_button_menu::~idea_UI_button_menu()
{
	
}
