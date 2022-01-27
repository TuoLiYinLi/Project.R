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
        if (instance ==nullptr) {
#ifdef _DEBUG
            SDL_Log(u8" ERROR:new UISystem()�����ڴ�ʧ��,ֵΪnullptr");
#endif // _DEBUG
        }
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

	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{

		//ˢ����괰������
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
			//���̰����¼������Բ鿴 SDL_KeyboardEvent �ṹ������

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
		}
		else if (evt.type == SDL_KEYUP)
		{
			//���̵����¼�

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
		}
		else if (evt.type == SDL_MOUSEBUTTONDOWN)
		{
			//��갴ť�����¼������Բ鿴 SDL_MouseButtonEvent �ṹ������

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
			//��갴ť�����¼������Բ鿴 SDL_MouseButtonEvent �ṹ������

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

	//�������
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

	//�����м�
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

	//�����Ҽ�
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

	//����ո��
	if(key_space_state&&!key_space_last)
	{
		key_space_press = true;
	}else
	{
		key_space_press = false;
	}

	//����f3����
	if (key_f3_state && !key_f3_last)
	{
		key_f3_press = true;
	}
	else
	{
		key_f3_press = false;
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

	keydown_esc = false;
}

UISystem::~UISystem()
{
	SDL_Log("UISystem destruct");
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
	//�Ŵ���С����
	if(mouse_wheel_forward)
	{
		RenderingSystem::getInstance()->vs = VIEW_SPEED_SCALE_MAX;
	}else if(mouse_wheel_backward)
	{
		RenderingSystem::getInstance()->vs = -VIEW_SPEED_SCALE_MAX;
	}

	//���ƾ�ͷ�˶�
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

	//�л���ͣʱ��
	if(key_space_press)
	{
		GlobalData::flag_stop = !GlobalData::flag_stop;
	}

	//�л�����debug��ʾ
	if(key_f3_press)
	{
		GlobalData::flag_debug_physics = !GlobalData::flag_debug_physics;
	}

	//�˳���Ϸ
	if(keydown_esc)
	{
		GlobalData::flag_quit = true;
		SDL_Log(u8"now quit by keydown_esc");
	}


}
