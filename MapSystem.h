#pragma once
#include <iostream>

#include <vector>
#include "Grid.h"
#include "Chara.h"
#include "Facility.h"
class MapSystem
{
public:
	//获取单例实例
	static MapSystem* getInstance();
	//销毁单例实例
	void destroyInstance();

	std::vector<std::vector<Grid*>*>* map;//储存的所有Grid
	//获取特定位置的网格
	Grid* getGridAt(double x, double y);
	//获取特定位置网格的到王距离
	int getDTK(double x, double y);
	//获取特定位置网格的到王距离(走和游)
	int getDWTK(double x, double y);
	//角色覆盖到网格
	void occupyGrid(Chara* chara);
	//设施覆盖到网格
	void occupyGrid(Facility* facility);
	//报告内存使用情况
	void reportMemory();
	
protected:
	//构造函数
	MapSystem();
	//析构函数
	~MapSystem();
	//单例实例指针
	static MapSystem* instance;

};

