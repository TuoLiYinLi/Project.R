#include "Chara.h"

#include "PhysicsChara.h"
#include "Defined.h"
#include "SDL.h"


Chara* Chara::createNew()
{
	return new Chara();
}

PhysicsChara* Chara::getPhysicsChara() const
{
	return dynamic_cast<PhysicsChara*>(physics_object);
}

RenderingAnimation* Chara::getRenderingAnimation() const
{
	return dynamic_cast<RenderingAnimation*>(rendering_unit);
}


void Chara::update()
{
	//调用父级函数
	GameObject::update();
	//触发onImpact
	const int _impact = getPhysicsChara()->getImpact();
	if(_impact>0)onImpact(_impact);
	update_effect();
	update_attributes();
	update_animation();
	if (action_type == CharaActionType::idle)decide_action();
	if (action_type == CharaActionType::idle)onIdle();
	sync_animation();
}

void Chara::update_effect()
{
	//充能效果
	if (effect_charging > 0)
	{
		effect_charging--;
	}
	else
	{
		effect_charging = 0;
	}

	//抵抗效果时间
	if (effect_resistant > 0)
	{
		effect_resistant--;
	}
	else
	{
		effect_resistant = 0;
	}

	//中毒效果时间
	if (effect_poisoned > 0)
	{
		effect_poisoned--;
	}
	else
	{
		effect_poisoned = 0;
	}

	//燃烧效果
	if(effect_burning>0)
	{
		effect_burning--;
	}else
	{
		effect_burning = 0;
	}

	//封印效果
	if (effect_sealed > 0)
	{
		effect_sealed--;
	}
	else
	{
		effect_sealed = 0;
	}

	//盲目效果
	if (effect_blind > 0)
	{
		effect_blind--;
	}
	else
	{
		effect_blind = 0;
	}

	//眩晕效果
	if (effect_dizzy > 0)
	{
		effect_dizzy--;
	}
	else
	{
		effect_dizzy = 0;
	}
}

void Chara::update_attributes()
{
	//燃烧伤害
	if (effect_burning > 0)
	{
		onBurning();
		burning_damage_accumulation += BURNING_SPEED;
		const int delta = static_cast<int>(floor(burning_damage_accumulation));
		health -= delta;
		burning_damage_accumulation -= delta;
		if(health<0)
		{
			health = 0;
		}
	}else
	{
		burning_damage_accumulation = 0;
	}

	//中毒效果
	if (effect_poisoned > 0)
	{
		onPoisoned();
		poisoned_damage_accumulation += health * POISONED_SPEED;
		const int delta = static_cast<int>(floor(poisoned_damage_accumulation));
		health -= delta;
		poisoned_damage_accumulation -= delta;
		if(health<0)
		{
			health = 0;
		}
	}else
	{
		poisoned_damage_accumulation = 0;
	}

	//氧气系统
	if(getPhysicsChara()->detectSubmersed())
	{
		//被水淹没
		oxygen--;
		if(oxygen<0)
		{
			//缺氧
			oxygen = 0;
			oxygen_damage_accumulation += health_max * OXYGEN_DAMAGE;
			const int delta = static_cast<int>(floor(oxygen_damage_accumulation));
			health -= delta;
			oxygen_damage_accumulation -= delta;
			if (health < 0)
			{
				health = 0;
			}
		}
	}else
	{
		//被没有被水淹没
		oxygen++;
		if (oxygen>OXYGEN_MAX)
		{
			oxygen = OXYGEN_MAX;
		}
		oxygen_damage_accumulation = 0;
	}

	if(health<=0&&action_type!=CharaActionType::dead)
	{
		setAnimationDead();
	}

	//生命值恢复
	if (effect_poisoned <= 0)
	{
		health_recovery_accumulation += health_recovery_speed;
		const int delta = static_cast<int>(floor(health_recovery_accumulation));
		health += delta;
		health_recovery_accumulation -= delta;
		if(health>health_max)
		{
			health = health_max;
		}
	}
}

void Chara::update_animation() {

	//推进动画
	animation_progress++;

	switch (action_type)
	{
	case CharaActionType::idle:
		//当前是闲置状态
		{
			if (getPhysicsChara()->getIfFalling()
			|| getPhysicsChara()->getIfHitBack())
			{
				//角色物理体受到打断
				setAnimationDisturbed();
			}
			else if (animation_progress >= animation_length_idle)
			{
				//重复闲置动画
				animation_progress = 0;
			}
		}
		break;

	case CharaActionType::moving:
		onMoving();
		{
			//主动移动状态
			if (getIfMoving())
			{
				//仍然处于运动状态
				if (animation_progress >= animation_length_moving)
				{
					animation_progress = 0;
				}
			}
			else
			{
				//退出移动动画
				setAnimationIdle();
			}
		}
		break;

	case CharaActionType::disturbed:
		{
			//被打断状态
			if (getIfDisturbed())
			{
				//仍然处于被打断状态
				if (animation_progress >= animation_length_disturbed)
				{
					animation_progress = 0;
				}
			}
			else
			{
				//退出打断动画
				setAnimationIdle();
			}
		}
		break;

	case CharaActionType::skill_basic:
		{
			if(animation_progress == delay_skill_basic)
			{
				onBasicSkill();
			}

			//使用基本技能状态
			if (getIfDisturbed())
			{
				//角色物理体受到打断
				setAnimationDisturbed();
			}
			else if (animation_progress >= animation_length_skill_basic)
			{
				setAnimationIdle();
			}
		}
		break;

	case CharaActionType::skill_special:
		{
			if (animation_progress == delay_skill_special)
			{
				onSpecialSkill();
			}
			//使用特殊能力状态
			if (getIfDisturbed())
			{
				//角色物理体受到打断
				setAnimationDisturbed();
			}
			else if (animation_progress >= animation_length_skill_special)
			{
				setAnimationIdle();
			}
		}
		break;

	case CharaActionType::dead:
		{
			//死亡状态
			if (animation_progress >= animation_length_dead)
			{
				//已经播放完死亡动画
				onDead();
				flag_destroy = true;
				flag_static = true;
			}
		}
		break;
	}
}

void Chara::decide_action()
{
	
}


void Chara::sync_animation()
{
	switch (action_type)
	{
	case CharaActionType::idle:
		//当前是闲置状态
	{
		getRenderingAnimation()->setTexture(animation_type_idle, animation_length_idle, animation_progress);
	}
	break;

	case CharaActionType::moving:
		onMoving();
		{
			getRenderingAnimation()->setTexture(animation_type_moving, animation_length_moving, animation_progress);
		}
		break;

	case CharaActionType::disturbed:
	{
		getRenderingAnimation()->setTexture(animation_type_disturbed, animation_length_disturbed, animation_progress);
	}
	break;

	case CharaActionType::skill_basic:
	{
		getRenderingAnimation()->setTexture(animation_type_skill_basic, animation_length_skill_basic, animation_progress);
	}
	break;

	case CharaActionType::skill_special:
	{
		getRenderingAnimation()->setTexture(animation_type_skill_special, animation_length_skill_special, animation_progress);
	}
	break;

	case CharaActionType::dead:
	{
		getRenderingAnimation()->setTexture(animation_type_dead, animation_length_dead, animation_progress);
	}
	break;
	}

	//刷新角色朝向
	if (getPhysicsChara()->getDirection() == CharaDirection::right)
	{
		getRenderingAnimation()->setFlip(false);
	}
	else if (getPhysicsChara()->getDirection() == CharaDirection::left)
	{
		getRenderingAnimation()->setFlip(true);
	}

	//刷新角色位置
	getRenderingAnimation()->x = getPhysicsChara()->X;
	getRenderingAnimation()->y = getPhysicsChara()->Y;
	getRenderingAnimation()->width = getPhysicsChara()->bodyX * PIXEL_RATE;
	getRenderingAnimation()->height = getPhysicsChara()->bodyY * PIXEL_RATE;

	//刷新深度
	update_depth();
}

void Chara::update_depth()const
{
	rendering_unit->depth = DEPTH_WORLD_CHARA + static_cast<float>(physics_object->Y);
}




int Chara::chara_num = 0;

Chara::Chara()
{
	chara_num++;

	name = L"default_character";

	type_game_object = GameObjectType::default_chara;

	action_type = CharaActionType::idle;

	//设定物理体
	{
		physics_object = PhysicsChara::createNew();
		physics_object->game_object = this;

		physics_object->type_ally = AllyType::neutral;

		getPhysicsChara()->bodyX = 1;
		getPhysicsChara()->bodyY = 1;

		getPhysicsChara()->can_fly = false;
		getPhysicsChara()->can_swim = false;
		getPhysicsChara()->steady = false;
	}

	//设置角色动画
	{
		rendering_unit = RenderingAnimation::createNew();

		sync_animation();

		animation_progress = 0;

		animation_length_idle = 40;
		animation_length_moving = 30;
		animation_length_skill_basic = 40;
		animation_length_skill_special = 40;
		animation_length_disturbed = 40;
		animation_length_dead = 60;

		delay_skill_basic = 0;
		delay_skill_special = 0;

		animation_type_idle = AnimationType::debug_sequence_white;
		animation_type_moving = AnimationType::debug_sequence_white;
		animation_type_skill_basic = AnimationType::debug_sequence_blue;
		animation_type_skill_special = AnimationType::debug_sequence_red;
		animation_type_disturbed = AnimationType::debug_sequence_green;
		animation_type_dead = AnimationType::debug_sequence_black;
	}

	//设置角色属性
	{
		moving_speed = LOW_SPEED;

		health_max = 4;
		health = 4;
		health_recovery_speed = 0.2/60;
		health_recovery_accumulation = 0;

		burning_damage_accumulation = 0;
		poisoned_damage_accumulation = 0;
		oxygen_damage_accumulation = 0;

		magic_max = 4;
		magic = 4;
		magic_recovery_speed = 0.2/60;
		magic_recovery_accumulation = 0;

		stamina_max = 4;
		stamina = 4;
		stamina_recovery_speed = 0.2/60;
		stamina_recovery_accumulation = 0;
		
		oxygen = OXYGEN_MAX;//氧气值
	}
	//角色计数物
	counting_container = CountingContainer::createNew();

	//设置角色效果
	{
		effect_charging = 0;
		effect_resistant = 0;
		effect_poisoned = 0;
		effect_burning = 0;
		effect_sealed = 0;
		effect_blind = 0;
		effect_dizzy = 0;
	}

}

Chara::~Chara()
{
	counting_container->destroy();

	chara_num--;
}

void Chara::setAnimationIdle()
{
	action_type = CharaActionType::idle;
	animation_progress = 0;
}

void Chara::setAnimationDead()
{
	onKill();
	action_type = CharaActionType::dead;
	animation_progress = 0;
}

void Chara::setAnimationDisturbed()
{
	action_type = CharaActionType::disturbed;
	animation_progress = 0;
}


int Chara::getCharaNum()
{
	return chara_num;
}

void Chara::setAnimationSkillBasic()
{
	action_type = CharaActionType::skill_basic;
	animation_progress = 0;
}

void Chara::setAnimationSkillSpecial()
{
	action_type = CharaActionType::skill_special;
	animation_progress = 0;
}

void Chara::setAnimationMoving()
{
	action_type = CharaActionType::moving;
	animation_progress = 0;
}

bool Chara::getIfDisturbed() const
{
	return getPhysicsChara()->getIfFalling()
		||getPhysicsChara()->getIfHitBack();
}

bool Chara::getIfMoving() const
{
	return getPhysicsChara()->getIfMoving()
		&& !getPhysicsChara()->getIfFalling()
		&& !getPhysicsChara()->getIfHitBack();
}

bool Chara::setDirection(CharaDirection d) const
{
	return getPhysicsChara()->setDirection(d);
}

void Chara::setPosition(int x, int y)
{
	getPhysicsChara()->setPosition(x, y);
	//设置动画
	this->setAnimationIdle();
	sync_animation();
}



void Chara::actMove(CharaDirection d)
{
	if (action_type != CharaActionType::idle)return;
	setAnimationMoving();
	getPhysicsChara()->setMotion(d, moving_speed, 1, false);
}

void Chara::actSkillBasic(CharaDirection d)
{
	if (setDirection(d) && action_type == CharaActionType::idle)
	setAnimationSkillBasic();
}

void Chara::actSkillSpecial(CharaDirection d)
{
	if (setDirection(d)&& action_type == CharaActionType::idle)
	setAnimationSkillSpecial();
}

void Chara::onBasicSkill()
{
	
}

void Chara::onBurning()
{
	
}

void Chara::onDead()
{

}

void Chara::onHit()
{
	
}

void Chara::onIdle()
{

}

void Chara::onImpact(int _impact)
{
	
}

void Chara::onKill()
{
	
}


void Chara::onMoving()
{
	
}

void Chara::onPoisoned()
{
	
}

void Chara::onSpecialSkill()
{
	
}

