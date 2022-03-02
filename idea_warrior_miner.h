#pragma once
#include "Warrior.h"
class idea_warrior_miner :
    public Warrior
{
public:
    static idea_warrior_miner* createNew();

    void onBasicSkill() override;
    void onSpecialSkill() override;
protected:
    idea_warrior_miner();

    void decide_action() override;
};

