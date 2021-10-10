#pragma once
#include "AnimSystem.h"
#include <list>
#include <iostream>

class Chara;
class Facility;

class Grid
{
public:

	std::list<Chara*>* charaList;//角色的列表
	std::list<Facility*>* facilityList;//含有的设施

	unsigned int x;//自身X
	unsigned int y;//自身Y

	int distToKing;//在移动上与魔王的距离格数
	int distToKing_walk;//在行走的距离上与魔王的格数

	//创建new Grid
	static Grid* createNew(int _x,int _y);
	//销毁这个Grid
	void destroy();


	//获取当前未释放的Grid数量
	static int getCurrentGridNum();

protected:
	//构造函数
	Grid(int _x, int _y);
	//析构函数
	~Grid();
	static int currentGridNum;
};

