#include "idea_UI_button_exit.h"

#include "RenderingSystem.h"

idea_UI_button_exit* idea_UI_button_exit::createNew()
{
	return new idea_UI_button_exit();
}

idea_UI_button_exit::idea_UI_button_exit()
{
	name = L"ÍË³ö°´Å¥";
	texture_default = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_default, 0);
	texture_highlight = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_highlight, 0);
	texture_pressed = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_pressed, 0);
	rendering_unit->setTexture(texture_default);
}


idea_UI_button_exit::~idea_UI_button_exit()
{
	
}
