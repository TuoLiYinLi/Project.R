#pragma once
#include "GameObject.h"

enum class FacilityState
{
	idle,
	activated,
	death
};

class Facility :
	public GameObject
{
public:
	static Facility* createNew();

	void update() override;

	FacilityState state;	//设施的状态
	int animation_progress;	//当前动画进度

	int animation_length_idle;	//停滞动画总时长,0代表没有动画
	int animation_length_activated;	//激活动画总时长,0代表没有动画
	int animation_length_death;	//死亡动画总时长,0代表没有动画

	int health;	//一个设施的生命值

protected:
	Facility();
	~Facility() override;
};

