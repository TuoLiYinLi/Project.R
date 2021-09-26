#pragma once
#include "SDL.h"
#include <iostream>
#include "GlobalData.h"
#include "AnimSystem.h"
#include "WorldSystem.h"
#include "CharaSlime.h"
#include "ProjChop.h"
#include "ProjSlimeBall.h"

class InputSystem
{
public:
	int mouse_window_x;
	int mouse_window_y;
	double mouse_world_x;
	double mouse_world_y;

	bool mousedown_left;
	bool mousedown_right;

	bool keydown_w;
	bool keydown_s;
	bool keydown_a;
	bool keydown_d;

	bool keydown_x;
	bool keydown_c;

	static InputSystem* getInstance();
	void destroyInstance();
	void handleEvent();
	void renewMouse();
protected:
	static InputSystem* instance;
	SDL_Event evt;
	InputSystem();
	~InputSystem();
};

