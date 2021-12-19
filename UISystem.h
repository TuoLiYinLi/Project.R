#pragma once

class UISystem
{
public:
	static UISystem* getInstance();
	static void destroyInstance();

	int mouseX_window;	
	int mouseY_window;	
	double mouseX_world;
	double mouseY_world;

	bool mouse_left_press;	//鼠标左键按下瞬间
	bool mouse_left_state;	//鼠标左键状态
	bool mouse_left_release;	//鼠标左键释放瞬间

	bool mouse_right_press;	//鼠标右键按下瞬间
	bool mouse_right_state;	//鼠标右键状态
	bool mouse_right_release;	//鼠标右键释放瞬间

	bool mouse_middle_press;	//鼠标中键按下瞬间
	bool mouse_middle_state;	//鼠标中键按下状态
	bool mouse_middle_release;	//鼠标中键弹起瞬间

	bool mouse_wheel_forward;	//鼠标滚轮远离
	bool mouse_wheel_backward;	//鼠标滚轮靠近

	bool keydown_w;	//按键W状态
	bool keydown_s;	//按键S状态
	bool keydown_a;	//按键A状态
	bool keydown_d;	//按键D状态

	bool key_space_state;	//按键space状态
	bool key_space_press;	//按键space按下瞬间

	bool keydown_esc;	//按键escape状态

	void pullEvent();	//处理输入事件

	void controlGame()const;	//将输入传入游戏

protected:
	bool mouse_left_last;	//鼠标左键上次状态
	bool mouse_right_last;	//鼠标右键上次状态
	bool mouse_middle_last;	//鼠标中间上次状态
	bool key_space_last;	//鼠标中间上次状态

	static UISystem* instance;

	UISystem();
	~UISystem();

	void renewMouseWorldPosition();	//更新鼠标世界坐标
};

