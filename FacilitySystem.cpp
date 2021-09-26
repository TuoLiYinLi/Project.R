#include "FacilitySystem.h"
#include "Defined.h"

FacilitySystem* FacilitySystem::instance = nullptr;

FacilitySystem* FacilitySystem::getInstance() {
	if (instance==nullptr) {
		instance = new FacilitySystem();
		if (instance == nullptr) {
#ifdef _DEBUG
			std::cout << "\t\tERROR:new FacilitySystem()申请内存失败,值为nullptr\n";
#endif // _DEBUG

		}
	}
	return instance;
}

FacilitySystem::FacilitySystem() {
#ifdef FACILITY_SYSTEM_DEBUG
	std::cout << "FacilitySystem::FacilitySystem()\n";
#endif // FACILITY_SYSTEM_DEBUG
	facilityList_static = new std::list<Facility*>();
	facilityList_dynamic = new std::list<Facility*>();
#ifdef _DEBUG
	if (facilityList_static==nullptr)
	{
		std::cout << "\t\tERROR:new std::list<Facility*>()-static申请内存失败,值为nullptr\n";
	}
	if (facilityList_dynamic == nullptr)
	{
		std::cout << "\t\tERROR:new std::list<Facility*>()-dynamic申请内存失败,值为nullptr\n";
	}
#endif // _DEBUG
}

void FacilitySystem::destroyInstance() {
	if (instance!=nullptr) {
		delete instance;
		instance = nullptr;
	}
}

FacilitySystem::~FacilitySystem() {
#ifdef FACILITY_SYSTEM_DEBUG
	std::cout << "FacilitySystem::~FacilitySystem()\n";
#endif // FACILITY_SYSTEM_DEBUG
	
	reportMemory();
	int count = 0;
	if (facilityList_static != nullptr) {
		for (auto it = facilityList_static->begin(); it != facilityList_static->end(); it++)
		{
			if ((*it) != nullptr) {
				(*it)->destroy();
				(*it) = nullptr;
				count++;
			}
		}
#ifdef FACILITY_SYSTEM_DEBUG
		std::cout << "\t\t销毁了facilityList_static中"<<count<<"个Facility\n";
#endif // FACILITY_SYSTEM_DEBUG
		delete facilityList_static;
		facilityList_static = nullptr;
	}
	count = 0;
	if (facilityList_dynamic != nullptr) {
		for (auto it = facilityList_dynamic->begin(); it != facilityList_dynamic->end(); it++)
		{
			if ((*it) != nullptr) {
				(*it)->destroy();
				(*it) = nullptr;
				count++;
			}
		}
#ifdef FACILITY_SYSTEM_DEBUG
		std::cout << "\t\t销毁了facilityList_dynamic中" << count << "个Facility\n";
#endif // FACILITY_SYSTEM_DEBUG
		delete facilityList_dynamic;
		facilityList_dynamic = nullptr;
	}
}


void FacilitySystem::reportMemory() {
#ifdef FACILITY_SYSTEM_DEBUG
	std::cout << "FacilitySystem::reportMemory()\n";
	std::cout << "\t\t现在有"<< Facility::getCurrentFacilityNum() <<"个Facility占用内存\n";
	std::cout << "\t\t静态设施列表长度"<< facilityList_static->size() <<"\n";
	std::cout << "\t\t动态设施列表长度" << facilityList_dynamic->size() << "\n";
#endif // FACILITY_SYSTEM_DEBUG

}

void FacilitySystem::removeFacility_static(Facility* facility)
{
	facility->destroy();
	facilityList_static->remove(facility);
}

std::list<Facility*>::iterator FacilitySystem::removeFacility_static(std::list<Facility*>::iterator it)
{
	(*it)->destroy();
	auto new_it = facilityList_static->erase(it);
	return new_it;
}

void FacilitySystem::removeFacility_dynamic(Facility* facility)
{
	facility->destroy();
	facilityList_dynamic->remove(facility);
}

std::list<Facility*>::iterator FacilitySystem::removeFacility_dynamic(std::list<Facility*>::iterator it)
{
	(*it)->destroy();
	auto new_it = facilityList_dynamic->erase(it);
	return new_it;
}



