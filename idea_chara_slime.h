#pragma once
#include "Chara.h"
class idea_chara_slime :
    public Chara
{
public:

    static idea_chara_slime* createNew();

	virtual void destroy();

	//死亡时(动画结束)触发
	virtual void onDeath();
	//不断触发(任何情况每帧)触发
	virtual void onAnytime();
	//使用基础能力时触发
	virtual void onBasicSkill();
	//当使用特殊能力时触发
	virtual void onSpecialSkill();
	//移动状态(击退/坠落/移动)时(每帧)触发
	virtual void onMove();
	//闲置状态时(每帧)触发
	virtual void onIdle();
	//发生撞击(击飞撞墙/强落地)时触发
	virtual void onImpact();
	//燃烧时(每帧)触发
	virtual void onBurning();
	//被投射物击中时触发
	virtual void onHit(Form* form);
	//繁殖完成时触发
	virtual void onBreed();

    //获取当前动作对应的动画种类
    virtual AnimType getAnimType();
protected:
	int heightMark;

	//史莱姆特有特性,按照方向一直前进
	DirectionType myDirection;
	//史莱姆逆时针转向
	void clockwise(bool ifReverse);

    idea_chara_slime();
    ~idea_chara_slime();
};

