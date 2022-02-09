#pragma once
#include "Monster.h"
class idea_monster_slime :
    public Monster
{
public:
    static idea_monster_slime* createNew();

    void update() override;

protected:
	//触发接口
	void onIdle()override;//当闲置状态时 每帧触发
	void onMoving()override;//当移动状态时 每帧触发
	void onBasicSkill()override;//当基础能力被使用时 单刻触发
	void onSpecialSkill()override;//当特殊能力被使用时 单刻触发
	void onKill()override;//当生命值归零时 单刻触发
	void onDead()override;//当死亡并消失时 单刻触发
	void onImpact(int _impact)override;//当受到外部冲击时 单刻触发
	void onHit()override;//当受到投射物直接伤害时 单刻触发
	void onBurning()override;//当自己燃烧时 每帧触发
	void onPoisoned()override;//当自己中毒时 每帧触发

protected:
    idea_monster_slime();
    ~idea_monster_slime()override;
};

