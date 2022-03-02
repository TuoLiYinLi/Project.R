#include "integration_counting_container.h"

#include <SDL_log.h>

int integration_counting_container::getNumOf(CountingType ct)
{
	for (auto it = list_counting_type.begin(); it != list_counting_type.end(); ++it)
	{
		if (it->type == ct)
		{
			return it->num;
		}
	}
	return 0;
}

void integration_counting_container::addNumOf(CountingType ct, int num)
{
	for (auto it = list_counting_type.begin(); it != list_counting_type.end(); ++it)
	{
		if (it->type == ct)
		{
			it->num += num;
			if (it->num <= 0) {
				list_counting_type.erase(it);
			}
			return;
		}
	}
	//˵��û�����ּ�����,�����������ּ�����
	if (num > 0) 
	{
		list_counting_type.push_front(CountingObject(ct, num));
	}
}

void integration_counting_container::removeNumOf(CountingType ct)
{
	for (auto it = list_counting_type.begin(); it != list_counting_type.end(); ++it)
	{
		if ((*it).type == ct)
		{
			list_counting_type.erase(it);
			return;
		}
	}
}

integration_counting_container::integration_counting_container()
{
	list_counting_type = std::list<CountingObject>();
}

CountingObject::CountingObject(CountingType _type, int _num)
{
	type = _type;
	num = _num;
}

std::list<CountingType> integration_counting_container::getAllTypes()
{
	std::list<CountingType> list_all_types = std::list<CountingType>();
	for (auto i = list_counting_type.begin(); i !=list_counting_type.end(); ++i)
	{
		list_all_types.push_back((*i).type);
	}

	list_all_types.sort();

	return list_all_types;
}

std::wstring integration_counting_container::getName(CountingType type)
{
	switch (type)
	{
	case CountingType::food: return L"ʳ��";
	case CountingType::slime: return L"ʷ��ķ";
	case CountingType::corpse: return L"ʬ��";
	case CountingType::energy: return L"����";
	case CountingType::corruption: return L"����";
	case CountingType::gems: return L"��ʯ";
	case CountingType::fire: return L"����";
	case CountingType::icy: return L"��˪";
	case CountingType::growth: return L"�ɳ�";
	}
#ifdef _DEBUG
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"һ��������û�ж�Ӧ����������");
	return L"δ֪";
#endif
}

