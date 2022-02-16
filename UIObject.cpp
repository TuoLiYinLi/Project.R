#include "UIObject.h"

#include "Defined.h"
#include "RenderingSystem.h"
#include "UISystem.h"

UIObject* UIObject::createNew()
{
	return new UIObject();
}

UIObject::UIObject()
{
	ui_object_num++;

	name = L"default_UI";

	flag_collider_enabled = true;
	flag_static = true;
	flag_mouse_in = false;

	collider_x = 0;
	collider_y = 0;
	collider_w = 100;
	collider_h = 100;

	rendering_unit = RenderingUnit::createNew();
	rendering_unit->reference = RenderingReference::window;

	rendering_unit->setTexture(RenderingSystem::getInstance()->getAnimation(AnimationType::debug_sequence_white, 0));

	update_depth(0);

	rendering_unit->x = 0;
	rendering_unit->y = 0;
	rendering_unit->width = 100;
	rendering_unit->height = 100;
	

	UISystem::getInstance()->list_ui_objects->push_front(this);
}

UIObject::~UIObject()
{
	if(rendering_unit)
	{
		rendering_unit->destroy();
		rendering_unit = nullptr;
	}

	UISystem::getInstance()->list_ui_objects->remove(this);

	ui_object_num--;
}

void UIObject::update_depth(float _d) const
{
	rendering_unit->depth = DEPTH_FIXED_UI+_d;
}


bool UIObject::checkColliderEnabled()const
{
	return flag_collider_enabled;
}

bool UIObject::checkMouseIn() const
{
	return flag_mouse_in;
}


int UIObject::ui_object_num = 0;

int UIObject::getUIObjectNum()
{
	return ui_object_num;
}

void UIObject::setPosition(int x, int y, int w, int h)
{
	collider_x = x;
	collider_y = y;
	collider_w = w;
	collider_h = h;

	rendering_unit->x = x;
	rendering_unit->y = y;
	rendering_unit->width = w;
	rendering_unit->height = h;
}


void UIObject::onMouseEnter()
{
	flag_mouse_in = true;
}

void UIObject::onMouseExit()
{
	flag_mouse_in = false;
}

void UIObject::onMouseDown()
{
	//SDL_Log("onMouseDown");
}

void UIObject::onMouseUp()
{
	//SDL_Log("onMouseUp");
}

void UIObject::onMousePressing()
{
	//SDL_Log("onMousePressing");
}

void UIObject::onMouseHanging()
{
	//SDL_Log("onMouseHanging");
}

void UIObject::onMouseRoll(bool forward)
{
	//SDL_Log("onMouseRoll%d",forward);
}
