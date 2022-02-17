#pragma once

#include "EnumAnimationType.h"
#include "RenderingUnit.h"

class GameObject;
class RenderingSystem;

//渲染单元 资源动画元件
class RenderingAnimation:
public RenderingUnit
{
public:
	//创建新的动画元件
	static RenderingAnimation* createNew();

	void setTexture(AnimationType type, int time_length, int current);
protected:
	RenderingAnimation();
	~RenderingAnimation() override;
};

