#include "Grid_old.h"
#include "Defined.h"
Grid_old::Grid_old(int _x, int _y) {
	Grid_old::currentGridNum++;

	charaList = new std::list<Chara_old*>();
#ifdef _DEBUG
	if(charaList==nullptr){
		std::cout << "\t\tERROR:Grid_old::new std::list<Chara_old*>()申请内存失败,值是nullptr\n";
	}
#endif // _DEBUG
	facilityList = new std::list<Facility_old*>();
#ifdef _DEBUG
	if (facilityList == nullptr) {
		std::cout << "\t\tERROR:Grid_old::new std::list<Facility_old*>()申请内存失败,值是nullptr\n";
	}
#endif // _DEBUG
	x = _x;
	y = _y;

	dist_to_king_shortest = -1;
	dist_to_king_walk = -1;
}

Grid_old::~Grid_old(){
#ifdef GRID_DEBUG
	std::cout << "\tGrid::~Grid_old()\n";
#endif // GRID_DEBUG

	if (charaList != nullptr) { delete charaList; }
	charaList = nullptr;
	if (facilityList != nullptr) { delete facilityList; }
	facilityList = nullptr;

	Grid_old::currentGridNum--;
}

int Grid_old::currentGridNum = 0;

int Grid_old::getCurrentGridNum() {
	return currentGridNum;
}

Grid_old* Grid_old::createNew(int _x, int _y) {
	Grid_old* g = new Grid_old(_x,_y);
	if (g == nullptr) {
#ifdef _DEBUG
		std::cout << "\t\tERROR:Grid_old::createNew()申请内存失败,值是nullptr\n";
#endif // _DEBUG
	}
	return g;
}

void Grid_old::destroy() {
	delete this;
}