#pragma once
class GameToolkit
{
public:
	//����������ת��Ϊ��������
	static void transPositionWorldToWindow(double x_world,double y_world,double* x_window,double* y_window);
	//����������ת��Ϊ��������
	static void transPositionWindowToWorld(double x_window, double y_window, double* x_world, double* y_world);

	//����str�й��ж����ַ��Լ����ж���1/2/3λ���ַ�(��4λ)
	static void getLengthUTF8(char const* str, int* cnt);
};

