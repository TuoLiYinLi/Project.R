#pragma once
#include "Chara.h"

enum class WarriorType
{
	default_warrior,
	miner,
};

//游戏物件 勇者
//我们的敌人
class Warrior :
    public Chara
{
public:
	static Warrior* createNew();//创建新的怪物

	WarriorType type_warrior;

	void update() override;

	static int getWarriorNum();

protected:

	static int warrior_num;

	Warrior();
	~Warrior()override;
};

