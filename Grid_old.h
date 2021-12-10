#pragma once
#include "AnimationSystem.h"
#include <list>
#include <iostream>

class Chara_old;
class Facility_old;

class Grid_old
{
public:

	std::list<Chara_old*>* charaList;//角色的列表
	std::list<Facility_old*>* facilityList;//含有的设施

	unsigned int x;//自身X
	unsigned int y;//自身Y

	int dist_to_king_shortest;//在移动上与魔王的距离格数
	int dist_to_king_walk;//在行走的距离上与魔王的格数

	//创建new Grid_old
	static Grid_old* createNew(int _x,int _y);
	//销毁这个Grid
	void destroy();


	//获取当前未释放的Grid数量
	static int getCurrentGridNum();

protected:
	//构造函数
	Grid_old(int _x, int _y);
	//析构函数
	~Grid_old();
	static int currentGridNum;
};

