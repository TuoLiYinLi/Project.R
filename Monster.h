#pragma once
#include "Chara.h"
class Monster :
    public Chara
{
public:
	static Monster* createNew();//创建新的怪物

	void update() override;

	void setPatrolArea(std::list<Grid*>* _grids);//设定巡逻区

	std::list <Grid*>* getPatrolArea()const;//获取巡逻区

	bool getIfInPatrolArea()const;//检查是否在巡逻区内

	static int getMonsterNum();

protected:
	//触发接口
	void onIdle()override;//当闲置状态时 每帧触发
	void onMoving()override;//当移动状态时 每帧触发
	void onBasicSkill()override;//当基础能力被使用时 单刻触发
	void onSpecialSkill()override;//当特殊能力被使用时 单刻触发
	void onKill()override;//当生命值归零时 单刻触发
	void onDead()override;//当死亡并消失时 单刻触发
	void onImpact()override;//当受到外部冲击时 单刻触发
	void onHit()override;//当受到投射物直接伤害时 单刻触发
	void onBurning()override;//当自己燃烧时 每帧触发
	void onPoisoned()override;//当自己中毒时 每帧触发

protected:
	static int monster_num;

	std::list<Grid*>* patrol_area;//怪物可以活动的区域

	Monster();
	~Monster()override;
};

