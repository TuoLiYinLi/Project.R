#include "InputSystem.h"
#include "Defined.h"
#include "GameToolkit.h"
InputSystem* InputSystem::getInstance()
{
    if (instance == nullptr) {
        instance = new InputSystem();
        if (instance ==nullptr) {
#ifdef _DEBUG
            std::cout << "\t\tERROR:new InputSystem()�����ڴ�ʧ��,ֵΪnullptr\n";
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
    while (SDL_PollEvent(&evt)) {
        //ˢ���������
        if (evt.type == SDL_MOUSEMOTION || evt.type == SDL_MOUSEBUTTONDOWN) {
            mouse_window_x = evt.button.x;
            mouse_window_y = evt.button.y;
            AnimSystem* animSys = AnimSystem::getInstance();
            double k = (1 / animSys->viewScale) * 0.03125;
            mouse_world_x = animSys->viewX + double(WINDOW_WIDTH) * 0.015625 + k * (mouse_window_x - double(0.5) * WINDOW_WIDTH);
            mouse_world_y = animSys->viewY + double(WINDOW_HEIGHT) * 0.015625 + k * (mouse_window_y - double(0.5) * WINDOW_HEIGHT);
#ifdef SHOW_KEY
            std::cout << "mouse_world:" << mouse_world_x << ',' << mouse_world_y << std::endl;
#endif
        }

        if (evt.type == SDL_QUIT) {
            GlobalData::quitFlag = true;
        }
        else if (evt.type == SDL_KEYDOWN) {
            //���̰����¼������Բ鿴 SDL_KeyboardEvent �ṹ������
#ifdef SHOW_KEY
            std::cout << "key down:" << evt.key.keysym.scancode << std::endl;
#endif   
            if (evt.key.keysym.scancode == SDL_SCANCODE_A) {
                keydown_a = true;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_D) {
                keydown_d = true;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_W) {
                keydown_w = true;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_S) {
                keydown_s = true;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_X) {
                keydown_x = true;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_C) {
                keydown_c = true;
            }
        }
        else if (evt.type == SDL_KEYUP) {
            //���̵����¼�
#ifdef SHOW_KEY
            std::cout << "key up:" << evt.key.keysym.scancode << std::endl;
#endif
            if (evt.key.keysym.scancode == SDL_SCANCODE_A) {
                keydown_a = false;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_D) {
                keydown_d = false;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_W) {
                keydown_w = false;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_S) {
                keydown_s = false;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_X) {
                keydown_x = false;
            }
            if (evt.key.keysym.scancode == SDL_SCANCODE_C) {
                keydown_c = false;
            }
        }
        else if (evt.type == SDL_MOUSEBUTTONDOWN) {
            //��갴ť�����¼������Բ鿴 SDL_MouseButtonEvent �ṹ������
#ifdef SHOW_KEY
            std::cout << "mouse down:"<< int(evt.button.button) << ',' << evt.button.x << ',' << evt.button.y << std::endl;
#endif
            //�������ɽ�սͶ����
            /*
            auto a = CharaSlime::createNew();
            a->x = floor(mouse_world_x);
            a->y = floor(mouse_world_y);
            a->renewPosition();

            a->ally = AllyType::ally;
            */

            //auto p = ProjSlimeBall::createNew();

            //p->x = mouse_world_x - 0.5;
            //p->y = mouse_world_y - 0.5;
            //p->allyType = AllyType::hostile;

            std::cout <<"distToKing:" << MapSystem::getInstance()->map->at(floor(mouse_world_x))->at(floor(mouse_world_y))->distToKing<< '\n';
            std::cout << "ifWalkable:" << gameToolkit::ifWalkable(floor(mouse_world_x),floor(mouse_world_y)) << '\n';
            std::cout << mouse_world_x<<"," << mouse_world_y << "\n";
            if (evt.button.button == SDL_BUTTON_LEFT) {
                mousedown_left = true;
            }
            if (evt.button.button == SDL_BUTTON_RIGHT) {
                mousedown_right = true;
            }
        }
        else if (evt.type == SDL_MOUSEBUTTONUP) {
            //��갴ť�����¼������Բ鿴 SDL_MouseButtonEvent �ṹ������
#ifdef SHOW_KEY
            std::cout << "mouse up:" << int(evt.button.button) << ',' << evt.button.x << ',' << evt.button.y << std::endl;
#endif
            if (evt.button.button == SDL_BUTTON_LEFT) {
                mousedown_left = false;
            }
            if (evt.button.button == SDL_BUTTON_RIGHT) {
                mousedown_right = false;
            }
        }
        else if(evt.type == SDL_MOUSEMOTION)
        {
#ifdef SHOW_KEY
            //std::cout << "mouse motion:" << int(evt.motion.xrel) << ',' << int(evt.motion.yrel) << std::endl;
#endif
            auto ap = ParticleGoldust::createNew();
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
