#pragma once
#include <string>
#include <iostream>
#include <list>

#include "Form.h"

#include "ActionType.h"
#include "AllyType.h"
#include "BreathType.h"
#include "MovingType.h"
#include "DirectionType.h"

#include "MapSystem.h"
#include "AnimSystem.h"

#include "CharaSystem.h"
class CharaSystem;

class Chara
{
public:
	std::string name;//角色名字
	AnimationUnit* animUnit;//角色动画单元
	Form form;//角色数值表单

	AllyType ally;//阵营

	int deathSpeed;//死亡动画时长
	int idleSpeed;//停滞动画时长
	int breath;//剩下多少氧气

	BreathType breathType;//角色的呼吸类型
	MovingType movingType;//角色的移动类型
	ActionType actionType;//正在进行的行动类型
	int animProgress;//动画播放的进度

	double x;//世界坐标X
	double y;//世界坐标Y

	double movingX;//在横向运动时距离剩余值
	double movingY;//在竖直方向运动时距离剩余值

	unsigned short bodyWidth;//角色宽度
	unsigned short bodyHeight;//角色高度

	int deltaX;//动画资源渲染偏移X
	int deltaY;//动画资源渲染偏移Y

	bool flip;//是否反向，是为左，否为右

	double burnDamage;//受到燃烧的累积伤害
	double poisionedDamage;//受到中毒的累积伤害
	double stifleDamage;//累积的呼吸伤害
	double recoverAccumulate;//生命值恢复累积
	double staminaAccumulate;//累积增加的st

	double fallingY;//由于坠落将要下降的距离
	int fallingDist;//从空中总共的坠落距离

	std::list<Grid*>* occupiedGrids;//占用的格位

	//创建新的角色
	static Chara* createNew();
	 //手动释放内存
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

	//使用移动能力
	void move(DirectionType d);
	//使用基础能力
	void useBasicSkill(bool flip);
	//使用特殊能力
	void useSpecialSkill(bool flip);
	//使用繁殖能力
	void breed();

	//刷新位置
	void renewPosition();
	//获取当前有多少个Chara
	static int getCurrentCharaNum();
	
protected:
	static int currentCharaNum;//记录有多少个Chara占用内存
	 Chara();
	~Chara();
};

