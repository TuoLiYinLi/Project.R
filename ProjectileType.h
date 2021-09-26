#pragma once
//投射物类型
enum class ProjectileType
{
	simple,//普通投射物()
	explosion,//爆炸投射物(范围)
	smoke,//烟雾投射物(持续)
};