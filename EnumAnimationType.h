#pragma once

enum class AnimationType
{
	default_banned,//默认贴图_禁用
	default_b,//默认贴图_蓝
	default_r,//默认贴图_红
	default_g,//默认贴图_绿

	physics_facility_air,//物理模型_设施_空阻挡
	physics_facility_liquid,//物理模型_设施_液体阻挡
	physics_facility_support,//物理模型_设施_支撑
	physics_facility_solid,//物理模型_设施_完全
	physics_chara,//物理模型_角色
	physics_projectile,//物理模型_投射物



	charaSlimeIdle,//史莱姆_停滞
	charaSlimeMove,//史莱姆_移动
	charaSlimeBasic,//史莱姆_普通能力
	charaSlimeSpecial,//史莱姆_特殊能力
	charaSlimeDeath,//史莱姆_死亡
	charaWarriorMiner1_idle,//矿工1_闲置
	charaWarriorMiner1_walk,//矿工1_行走
	charaWarriorMiner1_dig,//矿工1_挖掘
	charaWarriorMiner1_death,//矿工1_死亡
	gridDirt_1a,//网格泥土/阻挡/种类1
	gridDirt_1n,//网格泥土/无阻挡/种类1
	gridDirdCracked,//网格泥土/支撑/可破坏
	gridDirtStair_1L,//网格泥土阶梯/支撑/左/种类1
	gridDirtStair_1R,//网格泥土阶梯/支撑/右/种类1
	gridDirtStair_1B,//网格泥土阶梯/支撑/双/种类1
	gridDirtClimb_L_t1,//网格泥土攀爬/支撑/左/种类1
	gridDirtClimb_L_t2,//网格泥土攀爬/支撑/左/种类2
	gridGrass_h4,//网格草/h4
	gridDirtButton_1,//网格泥土/无阻挡/底部/种类1
	gridWater_1full,//网格水/填满
	gridWater_1upper,//网格水/未填满
	ladder,//梯子/默认在左侧
	ropeHead,//降绳头部/默认在右侧
	rope1,//降绳部分1/默认在右侧
	rope2,//降绳部分2/默认在右侧
	ropeTail,//降绳尾部/默认在右侧
	faciSlimeGlue_L1,//史莱姆粘液/1
	chopDown,//投射物/砍击/爆炸性
	slimeBall,//史莱姆粘液球
	particle_goldust,//粒子_金沙/
	size,//末尾，代表了总数量
};
