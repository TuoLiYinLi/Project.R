#include "CountingContainer.h"

#include <SDL_log.h>

CountingContainer* CountingContainer::createNew()
{
	return new CountingContainer();
}

void CountingContainer::destroy()const
{
	delete this;
}

int CountingContainer::getNumOf(CountingType ct)
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

void CountingContainer::addNumOf(CountingType ct, int num)
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
	//说明没有这种计数物,将会新增这种计数物
	if (num > 0) 
	{
		list_counting_type.push_front(CountingObject(ct, num));
	}
}

void CountingContainer::removeNumOf(CountingType ct)
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

CountingContainer::CountingContainer()
{
	list_counting_type = std::list<CountingObject>();
}

CountingContainer::~CountingContainer()
{
}

CountingObject::CountingObject(CountingType _type, int _num)
{
	type = _type;
	num = _num;
}

std::list<CountingType> CountingContainer::getAllTypes()
{
	std::list<CountingType> list_all_types = std::list<CountingType>();
	for (auto i = list_counting_type.begin(); i !=list_counting_type.end(); ++i)
	{
		list_all_types.push_back((*i).type);
	}

	list_all_types.sort();

	return list_all_types;
}

std::wstring CountingContainer::get_name(CountingType type)
{
	switch (type)
	{
	case CountingType::food: return L"食物";
	case CountingType::slimeGlue: return L"粘液";
	case CountingType::corpse: return L"尸体";
	case CountingType::energy: return L"能量";
	case CountingType::corruption: return L"腐化";
	case CountingType::gems: return L"宝石";
	case CountingType::fire: return L"火焰";
	case CountingType::icy: return L"冰霜";
	}
#ifdef _DEBUG
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"一个计数物没有对应的中文名称");
	return L"未知";
#endif
}

