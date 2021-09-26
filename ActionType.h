#pragma once
//角色动作的种类
enum class ActionType
{
	idle,//停滞
	move,//移动
	swim,//游泳
	basicSkill,//基础能力
	specialSkill,//特殊能力
	breed,//繁殖
	death,//死亡
	falling,//坠落
};