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
};

