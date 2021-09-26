#pragma once
#include <iostream>
#include "BlockingType.h"
#include "AnimSystem.h"
#include "StateType.h"
#include "MapSystem.h"
#include "Counting.h"
#include "AllyType.h"
#include "FacilitySystem.h"
class FacilitySystem;

class Facility
{
public:
	BlockingType blockingType;//表现出的阻挡类型
	StateType stateType;//运行状态
	AnimationUnit* animUnit;//持有的动画元件

	AllyType ally;//阵营

	Counting* counting;//设施含有的计数物

	int idleLength;//停滞动画总时长,0代表没有动画
	int activateLength;//激活动画总时长,0代表没有动画
	int deathLength;//死亡动画总时长,0代表没有动画
	int animProgress;//当前动画进度

	int health;//一个设施的生命值
	int activateCycle;//激活周期,值为0表示不能激活
	int activateCD;//激活倒计时
	
	int width;//宽度
	int height;//高度

	double x;//世界坐标X
	double y;//世界坐标Y

	std::list<Grid*>* occupiedGrids;//自身所占用的格子
	
	//创建new 设施
	static Facility* createNew();
	//销毁
	virtual void destroy();

	//任何时候触发
	virtual void onAnytime();
	//当被激活
	virtual void onActivate();
	//当闲置
	virtual void onIdle();
	//当被投射物击中
	virtual void onHit(Form* form);
	//当死亡
	virtual void onDeath();

	//获取当前动作对应的动画种类
	virtual AnimType getAnimType();


	//刷新自己的位置
	void renewPosition();
	//获取当前占用内存的设施数量
	static int getCurrentFacilityNum();
protected:
	static int currentNum;//当前占用内存的Facility数量
	Facility();
	~Facility();
};

