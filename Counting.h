#pragma once
#include <list>
#include <iostream>
#include "CountingType.h"

struct countingObject;

class Counting
{
public:
	//创建一组计数物
	static Counting* createNew();
	//销毁这一组计数物
	void destroy();
	//记录有哪些计数物以及它们的数量
	std::list<countingObject> cpList;
	//查询一种计数物的数量
	int getNumOf(CountingType ct);
	//增加一种计数物的数量
	void addNumOf(CountingType ct, int num);

protected:
	//从列表删除一种计数物
	
	//新增一种计数物

	Counting();
	~Counting();
};

struct countingObject
{
	CountingType type;
	int num;
	countingObject(CountingType _type,int _num);
};