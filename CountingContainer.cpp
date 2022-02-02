#include "CountingContainer.h"

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
		const CountingObject co = *it;
		if (co.type == ct)
		{
			return co.num;
		}
	}
	return 0;
}

void CountingContainer::addNumOf(CountingType ct, int num)
{
	for (auto it = list_counting_type.begin(); it != list_counting_type.end(); ++it)
	{
		CountingObject co = *it;
		if (co.type == ct)
		{
			co.num += num;
			if (co.num <= 0) {
				list_counting_type.erase(it);
				return;
			}
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

