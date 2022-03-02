#pragma once
#include "Chara.h"

enum class MonsterType
{
	default_monster,
	slime,
	slime_medium,
	slime_corrupt,
	slime_recombinant
};


//��Ϸ���� ����
//���ǵ�����
class Monster :
    public Chara
{
public:
	static Monster* createNew();//�����µĹ���

	MonsterType type_monster;

	void update() override;

	static int getMonsterNum();

protected:
	static int monster_num;

	Monster();
	~Monster()override;
};

