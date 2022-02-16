#pragma once
#include "SDL.h"
#include <string>

//接口 作为筛选器的目标
class abstract_inspect_target
{
public:
	virtual SDL_Texture* getThumbnail() = 0;//获取缩略图
	virtual std::wstring getBrief() = 0;//获取简报
	virtual std::wstring getMainInfo() = 0;//获取主要信息
	virtual std::wstring getDataInfo() = 0;//获取数据信息
	virtual std::wstring getExtraInfo() = 0;//获取额外信息
};

