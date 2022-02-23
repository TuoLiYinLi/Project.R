#pragma once
#include "Monster.h"
class idea_monster_slime :
    public Monster
{
public:
    static idea_monster_slime* createNew();

protected:
    idea_monster_slime();

	void decide_action() override;//AI
};

