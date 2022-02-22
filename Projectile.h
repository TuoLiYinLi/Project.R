#pragma once
#include "GameObject.h"

class Chara;

//游戏物体 投射物 不可实例化
class Projectile:
	public GameObject
{
public:
	void update() override;//更新行为

	RenderingAnimation* getRenderingAnimation()const;
	
	static int getProjectileNum();

	int damage;
	int effect_burning;
	int effect_poisoned;

	Chara* owner;

protected:
	Projectile();
	~Projectile() override;

	void sync_animation()const;
	void sync_flip()const;
	void update_depth()const;

	int animation_length;	//循环一次动画的时间
	int animation_progress;	//动画进度
	AnimationType animation_type;//动画

	int life_time;	//能够留存的时间

private:
	static int projectile_num;
};

