#pragma once
//动画的种类
enum class AnimType
{
	Default,//默认贴图
	charaSlimeIdle,//史莱姆_停滞
	charaSlimeMove,//史莱姆_移动
	charaSlimeBasic,//史莱姆_普通能力
	charaSlimeSpecial,//史莱姆_特殊能力
	charaSlimeDeath,//史莱姆_死亡
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
	faciSlimeGlue_L1,//史莱姆粘液/1
	chopDown,//投射物/砍击/爆炸性
	slimeBall,//史莱姆粘液球
	particle_goldust,//粒子_金沙/
	size,//末尾，代表了总数量
};