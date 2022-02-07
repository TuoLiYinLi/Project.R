#pragma once
#include "GameObject.h"
#include "PhysicsChara.h"

#include "CountingContainer.h"

enum class CharaActionType
{
	idle,//闲置
	moving,//移动
	skill_basic,//基本技能
	skill_special,//特殊技能
	disturbed,//被打断
	dead,//死亡
};

class Chara :
	public GameObject
{
public:
	static Chara* createNew();
	void update() override;

protected:
	PhysicsChara* getPhysicsChara() const;
	RenderingAnimation* getRenderingAnimation()const;

protected:
	CharaActionType action_type;//正在使用的动画类型

	//角色的动画
	int animation_progress;//当前动画进度
	int animation_length_idle;//停滞动画总时长,0代表没有动画
	int animation_length_moving;//激活动画总时长,0代表没有动画
	int animation_length_disturbed;//打断动画总时长,0代表没有动画
	int animation_length_skill_basic;//基础能力动画时长,0代表没有动画
	int animation_length_skill_special;//特殊能力动画时长,0代表没有动画
	int animation_length_dead;//死亡动画总时长,0代表没有动画

	int delay_skill_basic;//基础能力的触发倒数
	int delay_skill_special;//特殊能力的触发倒数

	AnimationType animation_type_idle;//闲置动画
	AnimationType animation_type_moving;//移动动画
	AnimationType animation_type_disturbed;//掉落动画
	AnimationType animation_type_skill_basic;//基本技能动画
	AnimationType animation_type_skill_special;//特殊技能动画
	AnimationType animation_type_dead;//死亡动画

public:
	//角色的属性

	double moving_speed;

	int health_max;//最大生命值
	int health;//生命值
	double health_recovery_speed;//生命值恢复速度
	double health_recovery_accumulation;//生命值恢复积累量

	double burning_damage_accumulation;//燃烧产生的累积伤害
	double poisoned_damage_accumulation;//中毒产生的累积伤害
	double oxygen_damage_accumulation;//缺氧产生累积伤害

	int magic_max;//最大魔力值
	int magic;//魔力值
	double magic_recovery_speed;//魔力值恢复速度
	double magic_recovery_accumulation;//魔力值积累量

	int stamina_max;//最大活力值
	int stamina;//活力值
	double stamina_recovery_speed;//活力值恢复速度
	double stamina_recovery_accumulation;//活力值累积量
	
	int oxygen;//氧气值

	//角色的计数物
	CountingContainer* counting_container;//计数物容器


	//角色效果
	int effect_charging;// 充能效果时间
	int effect_resistant;// 抵抗效果时间
	int effect_poisoned;// 中毒效果时间
	int effect_burning;// 燃烧效果时间
	int effect_sealed;// 封印效果时间
	int effect_blind;// 盲目效果时间
	int effect_dizzy;// 眩晕效果时间

	bool setDirection(CharaDirection d) const;//设置角色方向
	void setPosition(int x, int y);//传送角色到坐标位置

	void actMove(CharaDirection d) const; //进行移动
	virtual void actSkillSpecial(CharaDirection d);//使用特殊能力
	virtual void actSkillBasic(CharaDirection d);//使用基本能力

protected:
	//触发接口
	virtual void onIdle();//当闲置状态时 每帧触发
	virtual void onMoving();//当移动状态时 每帧触发
	virtual void onBasicSkill();//当基础能力被使用时 单刻触发
	virtual void onSpecialSkill();//当特殊能力被使用时 单刻触发
	virtual void onKill();//当生命值归零时 单刻触发
	virtual void onDead();//当死亡并消失时 单刻触发
	virtual void onImpact();//当受到外部冲击时 单刻触发
	virtual void onHit();//当受到投射物直接伤害时 单刻触发
	virtual void onBurning();//当自己燃烧时 每帧触发
	virtual void onPoisoned();//当自己中毒时 每帧触发
public:
	static int getCharaNum();

protected:
	Chara();
	~Chara() override;

	static int chara_num;

	void update_attributes();//更新属性数据
	void update_effect();//更新效果
	void update_animation();//更新行为和动画

	bool getIfDisturbed() const;//符合被打断状态的条件
	bool getIfMoving() const;//符合移动状态的条件

	void setAnimationIdle();//设置为闲置动画
	void setAnimationMoving();//设置为移动动画
	void setAnimationDisturbed();//设置为掉落动画
	void setAnimationSkillSpecial();//设置为特殊能力动画
	void setAnimationSkillBasic();//设置为普通能力动画
	void setAnimationDead();//设置为死亡动画

};

