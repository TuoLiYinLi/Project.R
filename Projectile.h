#pragma once
#include "GameObject.h"

class Projectile:
	public GameObject
{
public:
	//创建new 投射物
	static Projectile* createNew();
	
	int animation_length;	//循环一次动画的时间
	int animation_progress;	//动画进度
	int life_time;	//能够留存的时间
	
	static int getProjectileNum();
protected:
	Projectile();
	~Projectile() override;

private:
	static int projectile_num;
};

