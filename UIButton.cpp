#include "UIButton.h"

#include "RenderingSystem.h"

UIButton* UIButton::createNew()
{
	return new UIButton();
}

UIButton::UIButton()
{
	name = L"default_button";

	texture_default = RenderingSystem::getInstance()->getAnimation(AnimationType::debug_sequence_white, 0);
	texture_highlight = RenderingSystem::getInstance()->getAnimation(AnimationType::debug_sequence_yellow, 0);
	texture_pressed = RenderingSystem::getInstance()->getAnimation(AnimationType::debug_sequence_red, 0);

	rendering_unit->setTexture(texture_default);

	callback_f = nullptr;
}

UIButton::~UIButton()
{
	
}

void UIButton::onMouseUp()
{
	UIObject::onMouseUp();
	rendering_unit->setTexture(texture_highlight);

	if(callback_f)
	{
		callback_f();
	}
}

void UIButton::onMousePressing()
{
	UIObject::onMousePressing();
	rendering_unit->setTexture(texture_pressed);
}

void UIButton::onMouseEnter()
{
	UIObject::onMouseEnter();
	rendering_unit->setTexture(texture_highlight);
}

void UIButton::onMouseExit()
{
	UIObject::onMouseExit();
	rendering_unit->setTexture(texture_default);
}

void UIButton::setCallback(void (* _function_name)())
{
	callback_f = _function_name;
}
