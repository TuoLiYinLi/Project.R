#pragma once
#include "GameObject.h"

enum class CharaAction
{
	idle,
	moving,
	falling,
	skill_basic,
	skill_special,
	death
};

class Chara :
	public GameObject
{
public:
	static Chara* createNew();

	CharaAction action;//正在进行的行动类型
	int animation_progress;	//当前动画进度

	int animation_length_idle;	//停滞动画总时长,0代表没有动画
	int animation_length_moving;	//激活动画总时长,0代表没有动画
	int animation_length_falling;	//
	int animation_length_death;	//死亡动画总时长,0代表没有动画


	

protected:
	Chara();
	~Chara() override;
};

