#include "MapSystem.h"
#include "Defined.h"

MapSystem* MapSystem::getInstance() {
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "MapSystem::getInstance()\n";
#endif // MAP_SYSTEM_DEBUG
	if (instance == nullptr) {
		instance = new MapSystem();
	}
	return instance;
}

void MapSystem::destroyInstance() {
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "MapSystem::destroyInstance()\n";
#endif // MAP_SYSTEM_DEBUG

	if (instance!=nullptr) {
		delete instance;
		instance = nullptr;
	}
	return;
}

MapSystem* MapSystem::instance = nullptr;

MapSystem::MapSystem(){
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "MapSystem::MapSystem()" << std::endl;
	int verticalGridCount = 0;
#endif // MAP_SYSTEM_DEBUG
	map = new std::vector<std::vector<Grid*>*>(WORLD_WIDTH);
	for (auto it = map->begin(); it != map->end(); it++)
	{
		(*it) = new std::vector <Grid*>(WORLD_HEIGHT);
#ifdef MAP_SYSTEM_DEBUG
		verticalGridCount += 1;
#endif // MAP_SYSTEM_DEBUG
	}
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "\t\t创建竖直Grid列表数量:" << verticalGridCount << std::endl;
	int gridCount = 0;
#endif // MAP_SYSTEM_DEBUG
	int gridX = 0;
	int gridY = 0;
	for (auto it = map->begin(); it != map->end(); it++)
	{
		gridY = 0;
		for (auto ir = (*it)->begin(); ir != (*it)->end(); ir++)
		{
			(*ir) = Grid::createNew(gridX, gridY);
#ifdef MAP_SYSTEM_DEBUG
			gridCount += 1;
#endif // MAP_SYSTEM_DEBUG
			gridY++;
		}
		gridX++;
	}
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "\t\t初始化Grid数量:" << gridCount << std::endl;
	std::cout << "\t\tMapSystem初始化已经完成" << std::endl;
#endif // MAP_SYSTEM_DEBUG
}

MapSystem::~MapSystem() {
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "MapSystem::~MapSystem()" << std::endl;
	int gridCount = 0;
#endif // MAP_SYSTEM_DEBUG
	for (auto it = map->begin(); it != map->end(); it++)
	{
		for (auto ir = (*it)->begin(); ir != (*it)->end(); ir++)
		{
			if (*ir != nullptr) {
				(*ir)->destroy();
				(*ir) = nullptr;
#ifdef MAP_SYSTEM_DEBUG
				gridCount++;
#endif // MAP_SYSTEM_DEBUG
			}
		}
	}
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "\t\t销毁Grid数量:" << gridCount << std::endl;
	int verticalGridCount = 0;
#endif // MAP_SYSTEM_DEBUG
	for (auto it = map->begin(); it != map->end(); it++)
	{
		delete (*it);
#ifdef MAP_SYSTEM_DEBUG
		verticalGridCount++;
#endif // MAP_SYSTEM_DEBUG
	}
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "\t\t销毁竖直Grid列表数量:" << verticalGridCount << std::endl;
#endif // MAP_SYSTEM_DEBUG
	delete map;
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "\t\tMapSystem完成析构" << std::endl;
#endif // MAP_SYSTEM_DEBUG
	reportMemory();
}

Grid* MapSystem::getGridAt(int x, int y)
{
	if (x < 0 || x > WORLD_WIDTH - 1 ) 
	{
		throw x;
	}
	if (y < 0 || y > WORLD_HEIGHT - 1) 
	{
		throw y;
	}

	return map->at(x)->at(y);
}

void MapSystem::occupyGrid(Chara* chara)
{
	int x_start = round(chara->x-0.001);
	int y_start = round(chara->y - chara->bodyHeight + 1 - 0.001);
	int x_end = round(chara->x + chara->bodyWidth - 1 + 0.001);
	int y_end = round(chara->y + 0.001);

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			Grid* grid = map->at(i)->at(j);
			grid->charaList->push_back(chara);
			chara->occupiedGrids->push_back(grid);
		}
	}
}

void MapSystem::occupyGrid(Facility* facility)
{
	int x_start = round(facility->x - 0.001);
	int y_start = round(facility->y - 0.001);
	int x_end = round(facility->x + facility->width - 0.999);
	int y_end = round(facility->y + facility->height - 0.999);

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			Grid* grid = map->at(i)->at(j);
			grid->facilityList->push_back(facility);
			facility->occupiedGrids->push_back(grid);
		}
	}
}

void MapSystem::reportMemory() {
#ifdef MAP_SYSTEM_DEBUG
	std::cout << "MapSystem::reportMemory()" << std::endl;
	std::cout << "\t\t现在有"<<Grid::getCurrentGridNum()<<"个Grid占用内存" << std::endl;

#endif // MAP_SYSTEM_DEBUG
	return;
}

