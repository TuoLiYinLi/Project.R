#include "idea_projectile_slime_ball.h"

idea_projectile_slime_ball* idea_projectile_slime_ball::createNew()
{
	auto psb = new idea_projectile_slime_ball();
    return psb;
}

void idea_projectile_slime_ball::destroy()
{
	delete this;
}

void idea_projectile_slime_ball::onHit(Chara_old* c)
{
	c->onHit(&form);
}

void idea_projectile_slime_ball::onHit(Facility_old* f)
{
	f->onHit(&form);
}

void idea_projectile_slime_ball::onEnd()
{
}

idea_projectile_slime_ball::idea_projectile_slime_ball()
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

idea_projectile_slime_ball::~idea_projectile_slime_ball()
{
}
