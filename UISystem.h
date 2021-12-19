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

	bool mouse_left_press;	//����������˲��
	bool mouse_left_state;	//������״̬
	bool mouse_left_release;	//�������ͷ�˲��

	bool mouse_right_press;	//����Ҽ�����˲��
	bool mouse_right_state;	//����Ҽ�״̬
	bool mouse_right_release;	//����Ҽ��ͷ�˲��

	bool mouse_middle_press;	//����м�����˲��
	bool mouse_middle_state;	//����м�����״̬
	bool mouse_middle_release;	//����м�����˲��

	bool mouse_wheel_forward;	//������Զ��
	bool mouse_wheel_backward;	//�����ֿ���

	bool keydown_w;	//����W״̬
	bool keydown_s;	//����S״̬
	bool keydown_a;	//����A״̬
	bool keydown_d;	//����D״̬

	bool key_space_state;	//����space״̬
	bool key_space_press;	//����space����˲��

	bool keydown_esc;	//����escape״̬

	void pullEvent();	//���������¼�

	void controlGame()const;	//�����봫����Ϸ

protected:
	bool mouse_left_last;	//�������ϴ�״̬
	bool mouse_right_last;	//����Ҽ��ϴ�״̬
	bool mouse_middle_last;	//����м��ϴ�״̬
	bool key_space_last;	//����м��ϴ�״̬

	static UISystem* instance;

	UISystem();
	~UISystem();

	void renewMouseWorldPosition();	//���������������
};

