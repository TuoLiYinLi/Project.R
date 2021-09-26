#pragma once
#include <iostream>
#include <list>

#include "Form.h"
#include "ProjectileType.h"
#include "AllyType.h"

#include "Chara.h"
#include "Facility.h"
#include "MapSystem.h"



#include "ProjectileSystem.h"
class ProjectileSystem;

class Projectile
{
public:
	AllyType allyType;//这个投射物属于哪一方(我方投射物只击中敌人,敌方投射物只击中盟友,中立投射物击中双方)
	AnimationUnit* animUnit;//这个投射物的动画

	Form form;//这个发射物产生效果时对角色提交的数据表单
	
	double x;//世界坐标X
	double y;//世界坐标Y
	
	double vx;//本身的速度X
	double vy;//本身的速度y

	double ax;//本身的加速度x
	double ay;//本身的加速度y

	double bodyWidth;//体积宽度
	double bodyHeight;//体积高度
	
	unsigned int animCycle;//循环一次动画的时间
	unsigned int animProgress;//动画进度
	unsigned int livingTime;//能够留存的时间

	//当自然时间结束
	virtual void onEnd();
	//当飞行持续时
	virtual void onFlying();

	//创建new 投射物
	static Projectile* createNew();
	virtual void destroy();

	//获取当前占用内存的投射物数量
	static int getCurrentProjNum();
protected:
	Projectile();
	~Projectile();
	static int currentProjNum;
};

