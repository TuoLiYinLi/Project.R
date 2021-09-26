#include "ProjSlimeBall.h"

ProjSlimeBall* ProjSlimeBall::createNew()
{
	auto psb = new ProjSlimeBall();
    return psb;
}

void ProjSlimeBall::destroy()
{
	delete this;
}

void ProjSlimeBall::onHit(Chara* c)
{
	c->onHit(&form);
}

void ProjSlimeBall::onHit(Facility* f)
{
	f->onHit(&form);
}

void ProjSlimeBall::onEnd()
{
}

ProjSlimeBall::ProjSlimeBall()
{
	this->animCycle = 30;
	this->animUnit = AnimationUnit::createNew();
	this->animUnit->type = AnimType::slimeBall;
	this->allyType = AllyType::ally;
	this->animUnit->depth = 200;
	this->bodyHeight = 1;
	this->bodyWidth = 1;
	this->form.health = -1;
	this->livingTime = 60;
	this->vx = 0.05;
}

ProjSlimeBall::~ProjSlimeBall()
{
}
