#include "UISystem.h"
#include <iostream>

#include "RenderingSystem.h"
#include "GlobalData.h"
#include "Defined.h"
#include "GameToolkit.h"

UISystem* UISystem::getInstance()
{
    if (instance == nullptr) {
        instance = new UISystem();
    }
    return instance;
}

void UISystem::destroyInstance()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void UISystem::pullEvent()
{
	mouse_wheel_backward = false;
	mouse_wheel_forward = false;

	mouse_left_last = mouse_left_state;
	mouse_right_last = mouse_right_state;
	mouse_middle_last = mouse_middle_state;
	key_space_last = key_space_state;
	key_f3_last = key_f3_state;
	key_f4_last = key_f4_state;

	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{

		//刷新鼠标窗口坐标
		if (evt.type == SDL_MOUSEMOTION)
		{
			mouseX_window = evt.button.x;
			mouseY_window = evt.button.y;
		}

		if (evt.type == SDL_QUIT)
		{
			GlobalData::flag_quit = true;
		}
		else if (evt.type == SDL_KEYDOWN)
		{
			//键盘按下事件，可以查看 SDL_KeyboardEvent 结构体内容

			if (evt.key.keysym.scancode == SDL_SCANCODE_A)
			{
				keydown_a = true;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_D)
			{
				keydown_d = true;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_W)
			{
				keydown_w = true;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_S)
			{
				keydown_s = true;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				keydown_esc = true;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				key_space_state = true;
			}
			else if(evt.key.keysym.scancode == SDL_SCANCODE_F3)
			{
				key_f3_state = true;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_F4)
			{
				key_f4_state = true;
			}
		}
		else if (evt.type == SDL_KEYUP)
		{
			//键盘弹起事件

			if (evt.key.keysym.scancode == SDL_SCANCODE_A)
			{
				keydown_a = false;
			}else if (evt.key.keysym.scancode == SDL_SCANCODE_D)
			{
				keydown_d = false;
			}else if (evt.key.keysym.scancode == SDL_SCANCODE_W)
			{
				keydown_w = false;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_S)
			{
				keydown_s = false;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				keydown_esc = false;
			}
			else if(evt.key.keysym.scancode==SDL_SCANCODE_SPACE)
			{
				key_space_state = false;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_F3)
			{
				key_f3_state = false;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_F4)
			{
				key_f4_state = false;
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_1)
			{
				GlobalData::setTimeSpeed(TimeSpeedType::normal);
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_2)
			{
				GlobalData::setTimeSpeed(TimeSpeedType::double_speed);
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_3)
			{
				GlobalData::setTimeSpeed(TimeSpeedType::triple_speed);
			}
		}
		else if (evt.type == SDL_MOUSEBUTTONDOWN)
		{
			//鼠标按钮按下事件，可以查看 SDL_MouseButtonEvent 结构体内容

			if (evt.button.button == SDL_BUTTON_LEFT)
			{
				mouse_left_state = true;
			}else if (evt.button.button == SDL_BUTTON_RIGHT)
			{
				mouse_right_state = true;
			}else if (evt.button.button == SDL_BUTTON_MIDDLE)
			{
				mouse_middle_state = true;
			}
		}
		else if (evt.type == SDL_MOUSEBUTTONUP)
		{
			//鼠标按钮按下事件，可以查看 SDL_MouseButtonEvent 结构体内容

			if (evt.button.button == SDL_BUTTON_LEFT)
			{
				mouse_left_state = false;
			}else if (evt.button.button == SDL_BUTTON_RIGHT)
			{
				mouse_right_state = false;
			}else if (evt.button.button == SDL_BUTTON_MIDDLE)
			{
				mouse_middle_state = false;
			}
		}
		else if (evt.type == SDL_MOUSEMOTION)
		{

		}else if (evt.type == SDL_MOUSEWHEEL)
		{
			if (evt.wheel.y > 0)
			{
				mouse_wheel_forward = true;
				
			}else if(evt.wheel.y < 0)
			{
				mouse_wheel_backward = true;
			}
		}
	}

	//处理左键
	if(mouse_left_last&&!mouse_left_state)
	{
		mouse_left_release = true;
	}else
	{
		mouse_left_release = false;
	}

	if (!mouse_left_last && mouse_left_state)
	{
		mouse_left_press = true;
	}
	else
	{
		mouse_left_press = false;
	}

	//处理中键
	if (mouse_middle_last && !mouse_middle_state)
	{
		mouse_middle_release = true;
	}
	else
	{
		mouse_middle_release = false;
	}

	if (!mouse_middle_last && mouse_middle_last)
	{
		mouse_middle_press = true;
	}
	else
	{
		mouse_middle_press = false;
	}

	//处理右键
	if (mouse_right_last && !mouse_right_state)
	{
		mouse_right_release = true;
	}
	else
	{
		mouse_right_release = false;
	}

	if (!mouse_right_last && mouse_right_last)
	{
		mouse_right_press = true;
	}
	else
	{
		mouse_right_press = false;
	}

	//处理空格键
	if(key_space_state&&!key_space_last)
	{
		key_space_press = true;
	}else
	{
		key_space_press = false;
	}

	//处理f3按键
	if (key_f3_state && !key_f3_last)
	{
		key_f3_press = true;
	}
	else
	{
		key_f3_press = false;
	}

	//处理f4按键
	if (key_f4_state && !key_f4_last)
	{
		key_f4_press = true;
	}
	else
	{
		key_f4_press = false;
	}

	renewMouseWorldPosition();
}

UISystem* UISystem::instance = nullptr;

UISystem::UISystem()
{
	SDL_Log("UISystem construct");

    mouseX_window = 0;
    mouseY_window = 0;
    mouseX_world = 0;
    mouseY_world = 0;

	mouse_left_press = false;
	mouse_left_state = false;
	mouse_left_release = false;
	mouse_left_last = false;

	mouse_right_press = false;
	mouse_right_state = false;
	mouse_right_release = false;
	mouse_right_last = false;

	mouse_middle_press = false;
	mouse_middle_state = false;
	mouse_middle_release = false;
	mouse_middle_last = false;
	mouse_wheel_backward = false;
	mouse_wheel_forward = false;

    keydown_a = false;
    keydown_w = false;
    keydown_d = false;
    keydown_s = false;

	key_space_state = false;
	key_space_press = false;
	key_space_last = false;

	key_f3_state = false;
	key_f3_press = false;
	key_f3_last = false;

	key_f4_state = false;
	key_f4_press = false;
	key_f4_last = false;

	keydown_esc = false;

	last_tar = nullptr;

	list_ui_objects = new std::list<UIObject*>();
}

UISystem::~UISystem()
{
	SDL_Log("UISystem destruct");

	delete list_ui_objects;
}

void UISystem::renewMouseWorldPosition()
{
	/*
	const RenderingSystem* a = RenderingSystem::getInstance();
	const double k = 1 / a->viewScale * 0.03125;
	mouseX_world = a->viewX + double(WINDOW_WIDTH) * 0.015625 + k * (mouseX_window - double(0.5) *
		WINDOW_WIDTH);
	mouseY_world = a->viewY + double(WINDOW_HEIGHT) * 0.015625 + k * (mouseY_window - double(0.5) *
		WINDOW_HEIGHT);
	 */
	GameToolkit::transPositionWindowToWorld(mouseX_window, mouseY_window, &mouseX_world, &mouseY_world);
}

void UISystem::controlGame() const
{
	//放大缩小画面
	if(last_tar==nullptr)
	{
		if(mouse_wheel_forward)
		{
			RenderingSystem::getInstance()->vs = VIEW_SPEED_SCALE_MAX;
		}else if(mouse_wheel_backward)
		{
			RenderingSystem::getInstance()->vs = -VIEW_SPEED_SCALE_MAX;
		}
	}

	//控制镜头运动
	if (keydown_w)
	{
		RenderingSystem::getInstance()->vy = -VIEW_SPEED_Y_MAX;
	}else if (keydown_s)
	{
		RenderingSystem::getInstance()->vy = VIEW_SPEED_Y_MAX;
	}
	if(keydown_a)
	{
		RenderingSystem::getInstance()->vx = -VIEW_SPEED_X_MAX;
	}
	else if(keydown_d)
	{
		RenderingSystem::getInstance()->vx = VIEW_SPEED_X_MAX;
	}

	//切换暂停时间
	if(key_space_press)
	{
		GlobalData::flag_stop = !GlobalData::flag_stop;
	}

	//切换内置debug显示
	if(key_f3_press)
	{
		GlobalData::flag_debug_physics = !GlobalData::flag_debug_physics;
	}

	//切换game info debug显示
	if (key_f4_press)
	{
		GlobalData::flag_debug_game_info = !GlobalData::flag_debug_game_info;
	}

	//退出游戏
	if(keydown_esc)
	{
		GlobalData::flag_quit = true;
		SDL_Log(u8"now quit by keydown_esc");
	}


}

void UISystem::trigger_UIObjects()
{
	//寻找当前碰撞的UI元件
	float current_depth = 0;

	UIObject* current_tar = nullptr;

	for (auto i = list_ui_objects->begin(); i != list_ui_objects->end(); ++i)
	{
		if ((*i)->checkColliderEnabled() &&
			(*i)->rendering_unit->depth > current_depth &&
			GameToolkit::checkMouseInRange(
				(*i)->collider_x,
				(*i)->collider_y,
				(*i)->collider_w + (*i)->collider_x,
				(*i)->collider_y + (*i)->collider_h)
			)
		{
			current_depth = (*i)->rendering_unit->depth;
			current_tar = (*i);
		}
	}

	//开始触发
	if (current_tar)
	{
		if (mouse_left_press)current_tar->onMouseDown();
		else if (mouse_left_release)current_tar->onMouseUp();

		if (mouse_left_state)current_tar->onMousePressing();
		else current_tar->onMouseHanging();

		if (mouse_wheel_forward)current_tar->onMouseRoll(true);
		else if (mouse_wheel_backward)current_tar->onMouseRoll(false);
	}

	if (current_tar != last_tar)
	{
		if (current_tar)current_tar->onMouseEnter();
		if (last_tar)last_tar->onMouseExit();
	}

	last_tar = current_tar;
}