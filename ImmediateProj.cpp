#include "ImmediateProj.h"
#include "GameToolkit.h"

ImmediateProj* ImmediateProj::createNew()
{
	auto i = new ImmediateProj();
	return i;
}

void ImmediateProj::destroy()
{
	delete this;
}

void ImmediateProj::onHit(Chara_old* c)
{
}

void ImmediateProj::onHit(Facility_old* f)
{
}

void ImmediateProj::onEnd()
{
}

void ImmediateProj::onFlying()
{
	int x_start = round(x - 0.001);
	int y_start = round(y - 0.001);
	int x_end = round(x + bodyWidth - 0.999);
	int y_end = round(y + bodyHeight - 0.999);

	std::list<Chara_old*>* charaList=new std::list<Chara_old*>();
	std::list<Facility_old*>* faciList = new std::list<Facility_old*>();

	bool ifEnd = false;

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			Grid_old* grid = MapSystem::getInstance()->map->at(i)->at(j);
			//获取碰到的角色
			for (auto it = grid->charaList->begin(); it != grid->charaList->end(); it++)
			{
				if ((*it)->actionType != ActionType::death && gameToolkit::ifTarget(allyType, (*it)->ally)) {
					Chara_old* c = *it;
					charaList->push_back(c);
					ifEnd = true;
				}
			}
			//获取碰撞到的设施
			for (auto it = grid->facilityList->begin(); it != grid->facilityList->end(); it++)
			{
				if ((*it)->stateType != StateType::death && gameToolkit::ifTarget(allyType, (*it)->ally)) {
					Facility_old* f = *it;
					faciList->push_back(f);
					ifEnd = true;
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

	double minimal = this->bodyHeight * this->bodyHeight;
	Chara_old* tar_chara = nullptr;
	for (auto it = charaList->begin(); it != charaList->end(); it++)
	{
		Chara_old* c = *it;
		double current_dist = gameToolkit::rectCollisionVolume(x, y, bodyWidth, bodyHeight, c->x, c->y, c->bodyWidth, c->bodyHeight);
		if (minimal > current_dist) {
			minimal = current_dist;
			tar_chara = c;
		}
	}
	Facility_old* tar_faci = nullptr;
	for (auto it = faciList->begin(); it != faciList->end(); it++)
	{
		Facility_old* f = *it;
		double current_dist = gameToolkit::rectCollisionVolume(x, y, bodyWidth, bodyHeight, f->x, f->y, f->width, f->height);
		if (minimal > current_dist) {
			minimal = current_dist;
			tar_faci = f;
		}
	}
	delete charaList;
	delete faciList;
	if (tar_faci) {
		onHit(tar_faci);
	}
	else if (tar_chara) {
		onHit(tar_chara);
	}
}

ImmediateProj::ImmediateProj()
{
}

ImmediateProj::~ImmediateProj()
{
}
