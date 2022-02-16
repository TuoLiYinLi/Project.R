#pragma once
#include "abstract_inspect_target.h"
#include "CountingContainer.h"
#include "GameObject.h"
#include "PhysicsFacility.h"

enum class FacilityState
{
	idle,
	activated,
	dead
};

class Facility :
	public GameObject,public abstract_inspect_target
{
public:
	static Facility* createNew();

	void update() override;

	SDL_Texture* getThumbnail() override;
	std::wstring getBrief() override;

	std::wstring getMainInfo() override;
	std::wstring getDataInfo() override;
	std::wstring getExtraInfo() override;

protected:
	std::wstring science_name;//学名
	std::wstring introduction;//介绍信息
protected:

	FacilityState state;	//设施的状态
	int animation_progress;	//当前动画进度

	//设施的动画
	int animation_length_idle;	//停滞动画总时长,0代表没有动画
	int animation_length_activated;	//激活动画总时长,0代表没有动画
	int animation_length_dead;	//死亡动画总时长,0代表没有动画

	int activate_length;
	int activate_CD;

	int delay_activate;//激活后摇

	AnimationType animation_type_idle;//闲置动画
	AnimationType animation_type_activated;//激活动画
	AnimationType animation_type_dead;//死亡动画
public:
	//设施的属性
	int health;	//一个设施的生命值
	int health_max;//设施的最大生命值

	//设施的计数物
	CountingContainer* counting_container;//计数物容器

protected:
	//触发接口
	virtual void onIdle();//当闲置状态时 每帧触发
	virtual void onActivate();//当基础能力被使用时 单刻触发
	virtual void onKill();//当生命值归零时 单刻触发
	virtual void onDead();//当死亡并消失时 单刻触发
	virtual void onHit();//当受到投射物直接伤害时 单刻触发

	RenderingAnimation* getRenderingAnimation()const;
	PhysicsFacility* getPhysicsFacility()const;
public:
	void setPosition(int x, int y);//传送角色到坐标位置
	static int getFacilityNum();

protected:
	Facility();
	~Facility() override;

	void update_animation();//更新动画
	void sync_animation()const;//同步动画
	void update_depth()const;

	void setAnimationIdle();//设置为闲置动画
	void setAnimationActivate();//设置为激活动画
	void setAnimationDead();//设置为死亡动画

private:
	static int facility_num;
};

