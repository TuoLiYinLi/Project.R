#pragma once
#include "Warrior.h"
class idea_warrior_miner :
    public Warrior
{
public:
    static idea_warrior_miner* createNew();
protected:
    idea_warrior_miner();
};

