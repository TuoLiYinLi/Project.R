#pragma once

class InputSystem
{
public:
	static InputSystem* getInstance();
	static void destroyInstance();

	int mouseX_window;	//计划重构为只读
	int mouseY_window;
	double mouseX_world;
	double mouseY_world;

	bool mousedown_left;
	bool mousedown_right;

	bool keydown_w;
	bool keydown_s;
	bool keydown_a;
	bool keydown_d;

	bool keydown_x;
	bool keydown_c;

	bool keydown_esc;	//退出键

	void handleEvent();	//处理输入事件
	void renewMouse();	//尚未完成

protected:
	static InputSystem* instance;
	InputSystem();
	~InputSystem();
};

