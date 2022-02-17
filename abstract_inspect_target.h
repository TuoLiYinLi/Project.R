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

	void push_nullptr()const;//将对自己引用的指针置为空
	abstract_inspect_target** pointer_to_this_sizer_button = nullptr;//那个指向自己的指针的指针
	abstract_inspect_target** pointer_to_this_inspector = nullptr;//那个指向自己的指针的指针
};

