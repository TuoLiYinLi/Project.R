#pragma once
#include <iostream>
#include <string>
#include "Chara_old.h"
#include "Form.h"

#include "GeneSystem.h"
class GeneSystem;

//基因类
class Gene
{
public:
	std::string name;//基因的名字

	Form form;//基因的数值表单

	//基因的触发条件

	bool triggerOnBasicSkill;//在基本能力使用时触发
	bool triggerOnSpecialSkill;//在特殊能力使用时触发
	bool triggerOnMove;//在移动时触发
	bool triggerOnBreed;//在繁殖时触发
	bool triggerOnDeath;//在死亡时触发
	bool triggerOnAttacked;//被攻击时触发s
	bool triggerOnKilling;//在击败目标时触发

	//触发的结果

	/*
	virtual void onBasicSkill();//基本能力触发
	virtual void onSpecialSkill();//特殊能力触发
	virtual void onMove();//移动触发
	virtual void onBreed();//在繁殖时触发
	virtual void onDeath();//当死亡时触发
	virtual void onAttacked();//在被攻击时触发
	virtual void onKill();//当击败敌人时触发
	*/
	//生成新的默认基因
	static Gene* createNew();
	
	//销毁
	virtual void destroy();

	//获取当前占用内存的基因数量
	static int getCurrentNum();
protected:
	static int currentGeneNum;
	Gene();
	~Gene();
};

