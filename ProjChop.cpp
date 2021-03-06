#include "ProjChop.h"

ProjChop* ProjChop::createNew()
{
	auto pc = new ProjChop();
	return pc;
}

void ProjChop::destroy()
{
	delete this;
}

void ProjChop::onHit(Chara* c)
{
	auto f = std::find(hitCharaList->begin(), hitCharaList->end(), c);
	if (f == hitCharaList->end()) {
		hitCharaList->push_front(c);
		c->onHit(&form);
		//gameToolkit::applyForm(c, &(this->form));
	}
}

void ProjChop::onHit(Facility* f)
{
	auto find = std::find(hitFaciList->begin(), hitFaciList->end(), f);
	if (find == hitFaciList->end()) {
		hitFaciList->push_front(f);
		//近战仅对建筑造成1点伤害
		f->onHit(&form);
		//f->health -=1;
		//gameToolkit::createText(f->x, f->y, "-1", {255,255,255,255});
	}
}

ProjChop::ProjChop()
{
	hitCharaList = new std::list<Chara*>();
	hitFaciList = new std::list<Facility*>();

	this->animCycle = 20;
	this->animUnit = AnimationUnit::createNew();
	this->animUnit->type = AnimType::chopDown;
	this->animUnit->depth = 200;
	this->bodyHeight = 1;
	this->bodyWidth = 1;
	this->form.health = -2;
	this->livingTime = this->animCycle;
	this->vx = 0.02;
	this->ax = 0.001;

}

ProjChop::~ProjChop()
{
	if (hitCharaList)
	{
		delete hitCharaList;
	}
	if (hitFaciList) {
		delete hitFaciList;
	}
}
