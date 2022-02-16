#pragma once
#include "SDL.h"
#include <string>

//接口 作为筛选器的目标
class abstract_SizerTarget
{
public:
	virtual SDL_Texture* getThumbnail() = 0;//获取缩略图
	virtual std::wstring getBrief() = 0;//获取简报
};

