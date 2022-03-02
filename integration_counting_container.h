#pragma once
#include <list>
#include <string>

enum class CountingType
{
	food,//食物计数物
	slime,//史莱姆凝胶计数物
	corpse,//尸体计数物
	energy,//能量计数物
	corruption,//腐化计数物
	gems,//宝石计数物
	fire,//火焰计数物
	icy,//冰霜计数物
	growth,//成长计数物
};

//计数物对象
//储存计数物数据
struct CountingObject
{
	CountingType type;
	int num;
	CountingObject(CountingType _type,int _num);
};

//计数物容器
//有了它就可以附着计数物了
class integration_counting_container
{
public:
	integration_counting_container();
	//查询一种计数物的数量
	int getNumOf(CountingType ct);
	//增加一种计数物的数量
	void addNumOf(CountingType ct, int num);

	void removeNumOf(CountingType ct);//移除一种计数物

	std::list<CountingType> getAllTypes();

	static std::wstring getName(CountingType type);

protected:

	//记录有哪些计数物以及它们的数量
	std::list<CountingObject> list_counting_type;
};
