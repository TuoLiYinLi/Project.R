#pragma once
#include "Chara.h"

//游戏物体 怪物
//我们的主角
class Monster :
    public Chara
{
public:
	static Monster* createNew();//创建新的怪物

	void update() override;

	static int getMonsterNum();

protected:
	static int monster_num;

	Monster();
	~Monster()override;
};

