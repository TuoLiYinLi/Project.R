#pragma once
#include "SDL.h"
#include <string>

//�ӿ� ��Ϊɸѡ����Ŀ��
class abstract_SizerTarget
{
public:
	virtual SDL_Texture* getThumbnail() = 0;//��ȡ����ͼ
	virtual std::wstring getBrief() = 0;//��ȡ��
};

