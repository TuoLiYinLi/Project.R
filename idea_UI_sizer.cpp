#include "idea_UI_sizer.h"
#include "idea_UI_sizer_button.h"

#include "abstract_SizerTarget.h"
#include "Chara.h"
#include "Defined.h"
#include "Facility.h"
#include "GlobalData.h"
#include "PhysicsChara.h"
#include "UISystem.h"
#include "WorldSystem.h"
#include "RenderingSystem.h"

idea_UI_sizer* idea_UI_sizer::createNew()
{
	return new idea_UI_sizer();
}

idea_UI_sizer::idea_UI_sizer()
{
	name = L"ui_sizer";

	flag_enabled = false;
	flag_collider_enabled = true;
	flag_static = false;
	
	set_border_line_texture();

	update_depth(1);

	display_length = 0;
	content_length = 0;
	velocity = 0;
	obstruction = 18;
	position = 0;

	children = new std::list<idea_UI_sizer_button*>();

	disable();
}

idea_UI_sizer::~idea_UI_sizer()
{
	delete children;
}


void idea_UI_sizer::enable()
{
	//获取信息
	const int grid_x = static_cast<int>(floor(UISystem::getInstance()->mouseX_world));
	const int grid_y = static_cast<int>(floor(UISystem::getInstance()->mouseY_world));
	const auto g = WorldSystem::getInstance()->getGrid(grid_x, grid_y);
	if(!g)return;
	if (g->list_physics_chara->empty() && g->list_physics_facility->empty())return;

	//设定显示和逻辑参数
	flag_enabled = true;
	flag_static = false;
	flag_collider_enabled = true;
	rendering_unit->flag_enable = true;

	//设置按钮
	const int num = setup_buttons(grid_x, grid_y);

	//设置位置和大小

	int raw_h = (num * 18 + (num - 1)) * static_cast<int>(UI_SCALE);
	constexpr int raw_w = 18 * static_cast<int>(UI_SCALE);
	int raw_x = UISystem::getInstance()->mouseX_window - raw_w * 2;
	int raw_y = UISystem::getInstance()->mouseY_window - raw_w / 2;

	content_length = raw_h;

	if (raw_x < 0)raw_x = UISystem::getInstance()->mouseX_window + raw_w;

	if (content_length > static_cast<double>(WINDOW_HEIGHT) - 256)
	{
		raw_y = 128;
		raw_h = WINDOW_HEIGHT - 256;
	}
	else if (raw_y + raw_w >WINDOW_HEIGHT-128)
	{
		const int delta = raw_y + raw_w - WINDOW_HEIGHT + 128;
		raw_y -= delta;
	}else if (raw_y < 128)
	{
		raw_y = 128;
	}

	setPosition(raw_x, raw_y, raw_w, raw_h);

	rendering_unit->x -= UI_SCALE;
	rendering_unit->y -= UI_SCALE;
	rendering_unit->height += 2 * UI_SCALE;
	rendering_unit->width += 2 * UI_SCALE;
}

void idea_UI_sizer::disable()
{
	flag_enabled = false;
	flag_static = true;
	flag_collider_enabled = false;
	rendering_unit->flag_enable = false;

	//清理按钮
	clear_buttons();
}

int idea_UI_sizer::setup_buttons(int grid_x, int grid_y)
{

	const auto tar_grid = WorldSystem::getInstance()->getGrid(grid_x, grid_y);

	int count = 0;

	for (auto i = tar_grid->list_physics_chara->begin(); i != tar_grid->list_physics_chara->end(); ++i)
	{
		const auto c = reinterpret_cast<Chara*>((*i)->game_object);
		create_button(count * static_cast<int>(UI_SCALE) * 19, c);
		count++;
	}
	for (auto i = tar_grid->list_physics_facility->begin(); i != tar_grid->list_physics_facility->end(); ++i)
	{
		const auto f = reinterpret_cast<Facility*>((*i)->game_object);
		create_button(count * static_cast<int>(UI_SCALE) * 19, f);
		count++;
	}

	return count;
}

void idea_UI_sizer::clear_buttons() const
{
	if(children->empty())return;
	//清理按钮
	for (auto i = children->begin(); i != children->end(); ++i)
	{
		(*i)->readyToDestroy();
	}
	children->clear();
}



void idea_UI_sizer::update_position()
{
	position += velocity * GlobalData::getTimeDelta() / 1000;
	if (position + content_length <+ collider_h)
	{
		//按钮向上滚动到边界
		position =  + collider_h - content_length;
		velocity = 0;
	}else if(position>0)
	{
		//按钮向下滚动到边界
		velocity = 0;
		position = 0;
	}else
	{
		//在中间滑动
		if (velocity > 0)
		{
			velocity -= obstruction;
			if (velocity < 0)
			{
				velocity = 0;
			}
		}
		else if (velocity < 0)
		{
			velocity += obstruction;
			if (velocity > 0)
			{
				velocity = 0;
			}
		}
	}

}

void idea_UI_sizer::onMouseRoll(bool forward)
{
	UIObject::onMouseRoll(forward);
	if (forward)velocity = 900;
	else velocity = -900;
}

void idea_UI_sizer::updateOnRendering()
{
	if (!flag_enabled)return;
	update_position();
}

void idea_UI_sizer::create_button(int _offset, abstract_SizerTarget* _target)
{
	const auto b = idea_UI_sizer_button::createNew();

	b->name += L"_" + std::to_wstring(children->size());

	b->setup(this, _target, _offset);

	children->push_front(b);
}

void idea_UI_sizer::set_border_line_texture()const
{
	const auto t = SDL_CreateTexture(GlobalData::sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 1, 1);
	SDL_SetRenderTarget(GlobalData::sdl_renderer, t);
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 255, 255, 255, 255);
	SDL_RenderClear(GlobalData::sdl_renderer);

	rendering_unit->setTexture(t);
}	
