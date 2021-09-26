#include "PenetrableProj.h"
#include "GameToolkit.h"

PenetrableProj* PenetrableProj::createNew()
{
    return nullptr;
}

void PenetrableProj::destroy()
{
	delete this;
}

void PenetrableProj::onHit(Chara* c)
{
}

void PenetrableProj::onHit(Facility* f)
{
}

void PenetrableProj::onEnd()
{
}

void PenetrableProj::onFlying()
{
	int x_start = round(x - 0.001);
	int y_start = round(y - 0.001);
	int x_end = round(x + bodyWidth - 0.999);
	int y_end = round(y + bodyHeight - 0.999);

	bool ifEnd=false;

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			Grid* grid = MapSystem::getInstance()->map->at(i)->at(j);
			//获取碰到的角色
			for (auto it = grid->charaList->begin(); it != grid->charaList->end(); it++)
			{
				if ((*it)->actionType!=ActionType::death&&gameToolkit::ifTarget(allyType, (*it)->ally)) {
					onHit(*it);
				}
			}
			//获取碰撞到的设施
			for (auto it = grid->facilityList->begin(); it != grid->facilityList->end(); it++)
			{
				if ((*it)->stateType != StateType::death&&gameToolkit::ifTarget(allyType, (*it)->ally)){
					onHit(*it);
				}
				if ((*it)->blockingType == BlockingType::absolute) {
					ifEnd = true;
				}
			}
		}
	}
	if (ifEnd) {
		livingTime = 0;
	}
}

PenetrableProj::PenetrableProj()
{
}

PenetrableProj::~PenetrableProj()
{
}
