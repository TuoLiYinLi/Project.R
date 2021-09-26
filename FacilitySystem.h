#pragma once
#include <list>
#include "Facility.h"
class Facility;

class FacilitySystem
{
public:
	std::list<Facility*>* facilityList_static;//静态不变的设施的列表
	std::list<Facility*>* facilityList_dynamic;//动态变化的设施的列表
	//获取单例实例
	static FacilitySystem* getInstance();
	//销毁单例实例
	void destroyInstance();
	
	//从静态列表移除一个设施
	void removeFacility_static(Facility* facility);
	//用迭代器移除一个静态设施
	std::list<Facility*>::iterator removeFacility_static(std::list<Facility*>::iterator it);

	//从动态列表移除一个设施
	void removeFacility_dynamic(Facility* facility);
	//用迭代器移除一个动态设施
	std::list<Facility*>::iterator removeFacility_dynamic(std::list<Facility*>::iterator it);
	
	//汇报内存使用
	void reportMemory();
private:
	static FacilitySystem* instance;//单例实例
	FacilitySystem();
	~FacilitySystem();
};

