#pragma once
#include <list>
#pragma 

//�̳й����� ��¼��
//���Լ�¼ĳһ���͵Ķ���
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

