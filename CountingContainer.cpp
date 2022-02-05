#include "CountingContainer.h"

CountingContainer* CountingContainer::createNew()
{
	auto c = new CountingContainer();
	return c;
}

void CountingContainer::destroy()
{
	delete this;
}

int CountingContainer::getNumOf(CountingType ct)
{
	for (auto it = cpList.begin(); it != cpList.end(); it++)
	{
		CountingObject co = *it;
		if (co.type==ct)
		{
			return co.num;
		}
	}
	return 0;
}

void CountingContainer::addNumOf(CountingType ct, int num)
{
	for (auto it = cpList.begin(); it != cpList.end(); it++)
	{
		CountingObject co = *it;
		if (co.type == ct)
		{
			co.num += num;
			if (co.num <= 0) {
				cpList.erase(it);
#ifdef COUNTING_DEBUG
				std::cout << "\t\t移除了countingObject\n";
#endif // COUNTING_DEBUG
				return;
			}
		}
	}
	if (num > 0) 
	{
		auto new_co = CountingObject(ct, num);
		cpList.push_front(new_co);
#ifdef COUNTING_DEBUG
		std::cout << "\t\t创建了新countingObject\n";
#endif // COUNTING_DEBUG

	}
}

CountingContainer::CountingContainer()
{
#ifdef COUNTING_DEBUG
	std::cout << "\tCounting::CountingContainer()\n";
#endif // COUNTING_DEBUG
	cpList = std::list<CountingObject>();
}

CountingContainer::~CountingContainer()
{
#ifdef COUNTING_DEBUG
	std::cout << "\tCounting::~CountingContainer()\n";
#endif // COUNTING_DEBUG
}

CountingObject::CountingObject(CountingType _type, int _num)
{
	type = _type;
	num = _num;
}
