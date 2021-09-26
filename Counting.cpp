#include "Counting.h"
#include "Defined.h"

Counting* Counting::createNew()
{
	auto c = new Counting();
	return c;
}

void Counting::destroy()
{
	delete this;
}

int Counting::getNumOf(CountingType ct)
{
	for (auto it = cpList.begin(); it != cpList.end(); it++)
	{
		countingObject co = *it;
		if (co.type==ct)
		{
			return co.num;
		}
	}
	return 0;
}

void Counting::addNumOf(CountingType ct, int num)
{
	for (auto it = cpList.begin(); it != cpList.end(); it++)
	{
		countingObject co = *it;
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
		auto new_co = countingObject(ct, num);
		cpList.push_front(new_co);
#ifdef COUNTING_DEBUG
		std::cout << "\t\t创建了新countingObject\n";
#endif // COUNTING_DEBUG

	}
}

Counting::Counting()
{
#ifdef COUNTING_DEBUG
	std::cout << "\tCounting::Counting()\n";
#endif // COUNTING_DEBUG
	cpList = std::list<countingObject>();
}

Counting::~Counting()
{
#ifdef COUNTING_DEBUG
	std::cout << "\tCounting::~Counting()\n";
#endif // COUNTING_DEBUG
}

countingObject::countingObject(CountingType _type, int _num)
{
	type = _type;
	num = _num;
}
