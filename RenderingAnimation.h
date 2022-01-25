#pragma once

#include "EnumAnimationType.h"
#include "RenderingUnit.h"

class GameObject;
class RenderingSystem;

class RenderingAnimation:
public RenderingUnit
{
public:
	//�����µĶ���Ԫ��
	static RenderingAnimation* createNew();

	void setTexture(AnimationType type, int time_length, int current);
protected:
	RenderingAnimation();
	~RenderingAnimation() override;
};

