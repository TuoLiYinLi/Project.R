#pragma once
#include "SDL.h"
#include <string>

//�ӿ� ��Ϊɸѡ����Ŀ��
class abstract_inspect_target
{
public:
	virtual SDL_Texture* getThumbnail() = 0;//��ȡ����ͼ
	virtual std::wstring getBrief() = 0;//��ȡ��
	virtual std::wstring getMainInfo() = 0;//��ȡ��Ҫ��Ϣ
	virtual std::wstring getDataInfo() = 0;//��ȡ������Ϣ
	virtual std::wstring getExtraInfo() = 0;//��ȡ������Ϣ

	void push_nullptr()const;//�����Լ����õ�ָ����Ϊ��
	abstract_inspect_target** pointer_to_this_sizer_button = nullptr;//�Ǹ�ָ���Լ���ָ���ָ��
	abstract_inspect_target** pointer_to_this_inspector = nullptr;//�Ǹ�ָ���Լ���ָ���ָ��
};

