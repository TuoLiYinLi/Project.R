#include "InputSystem.h"
#include "Defined.h"
#include "GameToolkit.h"

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
	delete this;
}

void InputSystem::handleEvent()
{
	while (SDL_PollEvent(&evt))
	{
		//刷新鼠标坐标
		if (evt.type == SDL_MOUSEMOTION || evt.type == SDL_MOUSEBUTTONDOWN)
		{
			mouse_window_x = evt.button.x;
			mouse_window_y = evt.button.y;
			AnimSystem* animSys = AnimSystem::getInstance();
			double k = (1 / animSys->viewScale) * 0.03125;
			mouse_world_x = animSys->viewX + double(WINDOW_WIDTH) * 0.015625 + k * (mouse_window_x - double(0.5) *
				WINDOW_WIDTH);
			mouse_world_y = animSys->viewY + double(WINDOW_HEIGHT) * 0.015625 + k * (mouse_window_y - double(0.5) *
				WINDOW_HEIGHT);
#ifdef SHOW_KEY
            std::cout << "mouse_world:" << mouse_world_x << ',' << mouse_world_y << std::endl;
#endif
		}

		if (evt.type == SDL_QUIT)
		{
			GlobalData::quitFlag = true;
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
			if (evt.key.keysym.scancode == SDL_SCANCODE_1)
			{
				auto a = idea_chara_warrior_miner::createNew();
				a->x = floor(mouse_world_x);
				a->y = floor(mouse_world_y);
				a->renewPosition();
			}
			if (evt.key.keysym.scancode == SDL_SCANCODE_2)
			{
				auto a = idea_chara_slime::createNew();
				a->x = floor(mouse_world_x);
				a->y = floor(mouse_world_y);
				a->renewPosition();
			}
		}
		else if (evt.type == SDL_MOUSEBUTTONDOWN)
		{
			//鼠标按钮按下事件，可以查看 SDL_MouseButtonEvent 结构体内容
#ifdef SHOW_KEY
            std::cout << "mouse down:"<< int(evt.button.button) << ',' << evt.button.x << ',' << evt.button.y << std::endl;
#endif
			//测试生成近战投射物

			/*
			auto a = idea_chara_warrior_miner::createNew();
			a->x = floor(mouse_world_x);
			a->y = floor(mouse_world_y);
			a->renewPosition();

			a->ally = AllyType::ally;
			*/

			//网格内debug
			{
				auto tar_grid = MapSystem::getInstance()->map->at(floor(mouse_world_x))->at(floor(mouse_world_y));
				std::cout << "Debug at Grid (" << tar_grid->x << "," << tar_grid->y << ")\n";
				std::cout << "\tdistToKing:" << tar_grid->distToKing << '\n';
				std::cout << "\tdistToKing_walk:" << tar_grid->distToKing_walk << '\n';
				std::cout << "\tifWalkable:" << gameToolkit::ifWalkable(floor(mouse_world_x), floor(mouse_world_y)) <<
					'\n';
				int count = 0;
				for (auto i = tar_grid->charaList->begin(); i != tar_grid->charaList->end(); i++)
				{
					std::cout << "\tchara@" << count << " tag:" << int((*i)->tag) << '\n';
					count += 1;
				}
				count = 0;
				for (auto i = tar_grid->facilityList->begin(); i != tar_grid->facilityList->end(); i++)
				{
					std::cout << "\tfacility@" << count << " tag:" << int((*i)->tag) << '\n';
					count += 1;
				}
			}


			std::cout << "\n";
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
			//std::cout << "mouse motion:" << int(evt.motion.xrel) << ',' << int(evt.motion.yrel) << std::endl;
#endif
			auto ap = idea_particle_goldust::createNew();
			ap->x = mouse_world_x;
			ap->y = mouse_world_y;
			ap->animUnit->x = ap->x;
			ap->animUnit->y = ap->y;
			ap->animUnit->width = ap->w * ap->scale;
			ap->animUnit->height = ap->h * ap->scale;
		}
	}
}

InputSystem* InputSystem::instance = nullptr;

InputSystem::InputSystem()
{
    mouse_window_x = 0;
    mouse_window_y = 0;
    mouse_world_x = 0;
    mouse_world_y = 0;

    keydown_a = false;
    keydown_w = false;
    keydown_d = false;
    keydown_s = false;
    keydown_c = false;
    keydown_x = false;
    mousedown_left = false;
    mousedown_right = false;
}

InputSystem::~InputSystem()
{
}

void InputSystem::renewMouse()
{

}
