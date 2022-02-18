#pragma once
#include <list>
#pragma 

//继承工具类 记录器
//可以记录某一类型的对象
template<class T>
class integration_recorder
{
public:
	integration_recorder(){my_list = std::list<T*>();}
	bool record(T* target)
	{
		if (!check(target))
		{
			my_list.push_back(target);
			return true;
		}
		return false;
	}
	bool check(T* target) {
		auto i = std::find(my_list.begin(), my_list.end(), target);
		if (i != my_list.end())
		{
			return true;
		}
		else
			return false;
	}
	void clear(){my_list.clear();}
private:
	std::list<T*> my_list;
};

