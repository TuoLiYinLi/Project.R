#include "idea_UI_inspector_exit.h"

#include "GlobalData.h"
#include "idea_UI_inspector.h"
#include "RenderingSystem.h"

idea_UI_inspector_exit* idea_UI_inspector_exit::createNew()
{
	return new idea_UI_inspector_exit();
}

idea_UI_inspector_exit::idea_UI_inspector_exit()
{
	name = L"¼ìÊÓÆ÷ÍË³ö°´Å¥";
	texture_default = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_default, 0);
	texture_highlight = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_highlight, 0);
	texture_pressed = RenderingSystem::getInstance()->getAnimation(AnimationType::ui_button_exit_pressed, 0);
	rendering_unit->setTexture(texture_default);
}


idea_UI_inspector_exit::~idea_UI_inspector_exit()
{
	
}

void idea_UI_inspector_exit::enable()
{
	flag_collider_enabled = true;
	rendering_unit->flag_enable = true;
}
void idea_UI_inspector_exit::disable()
{
	flag_collider_enabled = false;
	rendering_unit->flag_enable = false;
}

void idea_UI_inspector_exit::onMouseUp()
{
	UIButton::onMouseUp();
	GlobalData::ui_inspector->disable();
}
