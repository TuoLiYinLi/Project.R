#pragma once
//设施的阻挡类型
enum class BlockingType
{
	no,//不进行阻挡
	liquid,//液体类型
	supportive,//支撑性的
	absolute,//完全阻挡
};