#pragma once

class InputSystem
{
public:
	static InputSystem* getInstance();
	static void destroyInstance();

	int mouseX_window;	//�ƻ��ع�Ϊֻ��
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

	bool keydown_esc;	//�˳���

	void handleEvent();	//���������¼�
	void renewMouse();	//��δ���

protected:
	static InputSystem* instance;
	InputSystem();
	~InputSystem();
};

