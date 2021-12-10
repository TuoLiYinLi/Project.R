#include "InputSystem.h"
#include <iostream>
#include "GlobalData.h"
#include "Defined.h"

InputSystem* InputSystem::getInstance()
{
    if (instance == nullptr) {
        instance = new InputSystem();
        if (instance ==nullptr) {
#ifdef _DEBUG
            std::cout << "\t\tERROR:new InputSystem()申请内存失败,值为nullptr\n";
#endif // _DEBUG
        }
    }

    return instance;
}

void InputSystem::destroyInstance()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void InputSystem::handleEvent()
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		//刷新鼠标坐标
		if (evt.type == SDL_MOUSEMOTION || evt.type == SDL_MOUSEBUTTONDOWN)
		{
			mouseX_window = evt.button.x;
			mouseY_window = evt.button.y;
			/*
			AnimationSystem* animSys = AnimationSystem::getInstance();
			double k = (1 / animSys->viewScale) * 0.03125;
			mouseX_world = animSys->viewX + double(WINDOW_WIDTH) * 0.015625 + k * (mouseX_window - double(0.5) *
				WINDOW_WIDTH);
			mouseY_world = animSys->viewY + double(WINDOW_HEIGHT) * 0.015625 + k * (mouseY_window - double(0.5) *
				WINDOW_HEIGHT);
			 */
#ifdef SHOW_KEY
            std::cout << "mouse_world:" << mouseX_world << ',' << mouseY_world << std::endl;
#endif
		}

		if (evt.type == SDL_QUIT)
		{
			GlobalData::flag_quit = true;
		}
		else if (evt.type == SDL_KEYDOWN)
		{
			//键盘按下事件，可以查看 SDL_KeyboardEvent 结构体内容
#ifdef SHOW_KEY
            std::cout << "key down:" << evt.key.keysym.scancode << std::endl;
#endif
			if (evt.key.keysym.scancode == SDL_SCANCODE_A)
			{
				keydown_a = true;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_D)
			{
				keydown_d = true;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_W)
			{
				keydown_w = true;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_S)
			{
				keydown_s = true;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_X)
			{
				keydown_x = true;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_C)
			{
				keydown_c = true;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				keydown_esc = true;
				GlobalData::flag_quit = true;
			}
		}
		else if (evt.type == SDL_KEYUP)
		{
			//键盘弹起事件
#ifdef SHOW_KEY
            std::cout << "key up:" << evt.key.keysym.scancode << std::endl;
#endif
			if (evt.key.keysym.scancode == SDL_SCANCODE_A)
			{
				keydown_a = false;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_D)
			{
				keydown_d = false;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_W)
			{
				keydown_w = false;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_S)
			{
				keydown_s = false;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_X)
			{
				keydown_x = false;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_C)
			{
				keydown_c = false;
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				keydown_esc = false;
			}
			/*
			 
			if (evt.key.keysym.scancode == SDL_SCANCODE_1)
			{
				auto a = idea_chara_warrior_miner::createNew();
				a->x = floor(mouseX_world);
				a->y = floor(mouseY_world);
				a->renewPosition();
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_2)
			{
				auto a = idea_chara_slime::createNew();
				a->x = floor(mouseX_world);
				a->y = floor(mouseY_world);
				a->renewPosition();
			}
			 */
		}
		else if (evt.type == SDL_MOUSEBUTTONDOWN)
		{
			//鼠标按钮按下事件，可以查看 SDL_MouseButtonEvent 结构体内容
#ifdef SHOW_KEY
            std::cout << "mouse down:"<< int(evt.button.button) << ',' << evt.button.x << ',' << evt.button.y << std::endl;
#endif

			if (evt.button.button == SDL_BUTTON_LEFT)
			{
				mousedown_left = true;
			}
			if (evt.button.button == SDL_BUTTON_RIGHT)
			{
				mousedown_right = true;
			}
		}
		else if (evt.type == SDL_MOUSEBUTTONUP)
		{
			//鼠标按钮按下事件，可以查看 SDL_MouseButtonEvent 结构体内容
#ifdef SHOW_KEY
            std::cout << "mouse up:" << int(evt.button.button) << ',' << evt.button.x << ',' << evt.button.y << std::endl;
#endif
			if (evt.button.button == SDL_BUTTON_LEFT)
			{
				mousedown_left = false;
			}
			if (evt.button.button == SDL_BUTTON_RIGHT)
			{
				mousedown_right = false;
			}
		}
		else if (evt.type == SDL_MOUSEMOTION)
		{
#ifdef SHOW_KEY
			std::cout << "mouse motion:" << int(evt.motion.xrel) << ',' << int(evt.motion.yrel) << std::endl;
#endif
		}
	}
}

InputSystem* InputSystem::instance = nullptr;

InputSystem::InputSystem()
{
	SDL_Log("InputSystem construct");

    mouseX_window = 0;
    mouseY_window = 0;
    mouseX_world = 0;
    mouseY_world = 0;

	mousedown_left = false;
    mousedown_right = false;
	
    keydown_a = false;
    keydown_w = false;
    keydown_d = false;
    keydown_s = false;
    keydown_c = false;
    keydown_x = false;
	keydown_esc = false;
}

InputSystem::~InputSystem()
{
	SDL_Log("InputSystem destruct");
}

void InputSystem::renewMouse()
{
	
}
