#pragma once
#include <list>

enum class CountingType
{
	food,//食物计数物
	slimeGlue,//史莱姆凝胶计数物
	corpse,//尸体计数物
	energy,//能量计数物
	corruption,//腐化计数物
	gems,//宝石计数物
	fire,//火焰计数物
	icy,//冰霜计数物
};

struct CountingObject
{
	CountingType type;
	int num;
	CountingObject(CountingType _type,int _num);
};

class CountingContainer
{
public:
	//创建一组计数物
	static CountingContainer* createNew();
	//销毁这一组计数物
	void destroy();
	//记录有哪些计数物以及它们的数量
	std::list<CountingObject> cpList;
	//查询一种计数物的数量
	int getNumOf(CountingType ct);
	//增加一种计数物的数量
	void addNumOf(CountingType ct, int num);

protected:
	//从列表删除一种计数物
	
	//新增一种计数物

	CountingContainer();
	~CountingContainer();
};
