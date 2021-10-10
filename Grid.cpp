#include "Grid.h"
#include "Defined.h"
Grid::Grid(int _x, int _y) {
	Grid::currentGridNum++;

	charaList = new std::list<Chara*>();
#ifdef _DEBUG
	if(charaList==nullptr){
		std::cout << "\t\tERROR:Grid::new std::list<Chara*>()申请内存失败,值是nullptr\n";
	}
#endif // _DEBUG
	facilityList = new std::list<Facility*>();
#ifdef _DEBUG
	if (facilityList == nullptr) {
		std::cout << "\t\tERROR:Grid::new std::list<Facility*>()申请内存失败,值是nullptr\n";
	}
#endif // _DEBUG
	x = _x;
	y = _y;

	distToKing = -1;
	distToKing_walk = -1;
}

Grid::~Grid(){
#ifdef GRID_DEBUG
	std::cout << "\tGrid::~Grid()\n";
#endif // GRID_DEBUG

	if (charaList != nullptr) { delete charaList; }
	charaList = nullptr;
	if (facilityList != nullptr) { delete facilityList; }
	facilityList = nullptr;

	Grid::currentGridNum--;
}

int Grid::currentGridNum = 0;

int Grid::getCurrentGridNum() {
	return currentGridNum;
}

Grid* Grid::createNew(int _x, int _y) {
	Grid* g = new Grid(_x,_y);
	if (g == nullptr) {
#ifdef _DEBUG
		std::cout << "\t\tERROR:Grid::createNew()申请内存失败,值是nullptr\n";
#endif // _DEBUG
	}
	return g;
}

void Grid::destroy() {
	delete this;
}