#include "Facility.h"
#include "Defined.h"

void Facility::onAnytime()
{
#ifdef FACILITY_DEBUG
	std::cout << "\t\tFacility::onAnytime()\n";
#endif // FACILITY_DEBUG
}

void Facility::onActivate()
{
#ifdef FACILITY_DEBUG
	std::cout << "\t\tFacility::activate()\n";
#endif // FACILITY_DEBUG
}

void Facility::onIdle()
{
#ifdef FACILITY_DEBUG
	std::cout << "\t\tFacility::onIdle()\n";
#endif // FACILITY_DEBUG
}

void Facility::onHit(Form* form)
{
#ifdef FACILITY_DEBUG
	std::cout << "\t\tFacility::onHit()\n";
#endif // FACILITY_DEBUG
}

void Facility::onDeath()
{
#ifdef FACILITY_DEBUG
	std::cout << "\t\tFacility::onDeath()\n";
#endif // FACILITY_DEBUG
}

AnimType Facility::getAnimType()
{
#ifdef _DEBUG
	std::cout << "\t\tERROR:Facility::getAnimType()不可调用未定义的虚函数\n";
#endif // _DEBUG
	return AnimType::size;
}

Facility* Facility::createNew() {
	auto f = new Facility();
	if (f == nullptr) {
#ifdef FACILITY_DEBUG
		std::cout << "\t\tERROR:new Facility()申请内存失败,值为nullptrs\n";
#endif // FACILITY_DEBUG

	}
	return f;
}

Facility::Facility() {
#ifdef FACILITY_DEBUG
	std::cout << "\tFacility::Facility()\n";
#endif // FACILITY_DEBUG
	currentNum++;

	blockingType = BlockingType::no;
	stateType = StateType::idle;
	animUnit = nullptr;

	ally = AllyType::ally;

	counting = Counting::createNew();

	idleLength = 0;
	activateLength = 0;
	deathLength = 0;
	animProgress = 0;

	health = 0;
	activateCD = 0;
	activateCycle = 0;

	width = 1;
	height = 1;
	
	x = 0;
	y = 0;
	activateCD = 0;
	activateCycle = 0;

	occupiedGrids = new std::list<Grid*>();
	renewPosition();
}

void Facility::destroy() {
	
	delete this;
}

Facility::~Facility() {
#ifdef FACILITY_DEBUG
	std::cout << "\tFacility::~Facility()\n";
#endif // FACILITY_DEBUG

	counting->destroy();

	if (animUnit != nullptr) {
		AnimSystem::getInstance()->removeAnimUnit(animUnit);
		animUnit = nullptr;
	}

	for (auto it = this->occupiedGrids->begin(); it != this->occupiedGrids->end(); it++)
	{
		Grid* grid = *it;
		grid->facilityList->remove(this);
		//std::cout << "remove 1\n";
	}
	this->occupiedGrids->clear();
	
	if (occupiedGrids!=nullptr) 
	{
		delete occupiedGrids;
		occupiedGrids = nullptr;
	}

	currentNum--;
}

int Facility::currentNum = 0;

void Facility::renewPosition()
{
	if (animUnit !=nullptr) {
		this->animUnit->x = this->x;
		this->animUnit->y = this->y;
	}
	for (auto it = occupiedGrids->begin(); it != occupiedGrids->end(); it++)
	{
		Grid* grid = *it;
		grid->facilityList->remove(this);
		//std::cout << "remove 1\n";
	}
	occupiedGrids->clear();
	MapSystem::getInstance()->occupyGrid(this);
}

int Facility::getCurrentFacilityNum() {
	return currentNum;
}