#pragma once
#include "Monster.h"
class idea_monster_slime :
    public Monster
{
public:
    static idea_monster_slime* createNew();

    void update() override;
    void onBasicSkill() override;
    void onSpecialSkill() override;

protected:
    idea_monster_slime();

	void decide_action() override;//AI

private:
    void turn_clockwise(bool reverse) const;

    bool can_go(PhysicsDirection direction) const;
};

