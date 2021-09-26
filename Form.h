#pragma once

#include <list>

//数值表单
class Form
{
public:
	//数值部分
	int healthMax;//最大生命值
	int health;//生命值
	double recovery;//生命恢复量,每帧计算
	
	int corruption;//腐化程度,达到100时直接死亡
	
	int stamina;//耐力值
	int staminaMax;//最大耐力值
	double staminaRecover;//耐力恢复量,每帧计算
	
	//行动的数值
	int moveTime;//移动动画的播放时间
	int moveST;//移动之后消耗的耐力
	
	int basicSkillTime;//基本能力动画的播放时间
	int basicSkillST;//使用基本能力消耗的耐力
	
	int specialSkillTime;//特殊能力动画播放时间
	int specialSkillST;//特殊能力消耗的耐力

	int breedSpeed;//繁殖动画的时间
	
	//效果部分
	int breedTime;//繁殖效果时间
	int speedupTime;//加速时间
	double speedupEffect;//加速后减少的角色动画时间百分比
	int sealedTime;//被封印的时间
	int vigorTime;//耐力恢复的时间
	double vigorEffect;//当处于活力状态,获得额外的活力恢复百分比
	int defenceTime;// 格挡的效果时间
	int burnTime;//燃烧效果时间
	double burnEffect;//每帧受到的燃烧伤害(正值表示受到的伤害数值)
	int stunnedTime;//眩晕效果时间
	double beatback;//击退效果数值
	int darkTime;//	黑暗效果时间
	int poisionedTime;//中毒效果时间
	double poisionedEffect;//中毒时每帧受到的百分比伤害

	//构造函数
	Form();
	//析构函数
	~Form();
	//设置基本数值
	void setBasicPart(
		int _healthMax = 0,
		int _health = 0,
		double _recovery = 0,
		int _staminaMax = 0,
		int _stamina = 0,
		double _staminaRecover = 0,
		int _corruption = 0);
	//设置行动数值
	void setActionPart(
		int _moveTime = 0,
		int _moveST = 0,
		int _basicSkillTime = 0,
		int _basicSkillST = 0,
		int _specialSkillTime = 0,
		int _specialSkillST = 0,
		int _breedSpeed = 0);
	//设置效果数值
	void setEffectPart(
		double _speedupEffect = 0,
		double _vigorEffect = 0,
		double _beatback = 0,
		double _poisionedEffect = 0,
		double _burnEffect = 0,
		int _breedTime = 0,
		int _speedupTime = 0,
		int _sealedTime = 0,
		int _vigorTime = 0,
		int _defenceTime = 0,
		int _burnTime = 0,
		int _stunnedTime = 0,
		int _darkTime = 0,
		int _poisionedTime = 0);
};

