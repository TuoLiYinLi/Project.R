#include "idea_facility_dirt_cracked.h"
#include "GameToolkit.h"


idea_facility_dirt_cracked* idea_facility_dirt_cracked::createNew()
{
	auto f=new idea_facility_dirt_cracked();
	return f;
}

void idea_facility_dirt_cracked::destroy()
{
    delete this;
}

void idea_facility_dirt_cracked::onHit(Form* form)
{
	health -= 1;
	if (health < 0) {
		health = 0;
	}
	gameToolkit::createText(x, y, "-1", { 255,255,255,255 });
}


AnimType idea_facility_dirt_cracked::getAnimType()
{
	return AnimType::gridDirdCracked;
}

idea_facility_dirt_cracked::idea_facility_dirt_cracked()
{
	blockingType = BlockingType::absolute;
	ally = AllyType::neutral;
	idleLength = 0;
	activateLength = 0;
	deathLength = 0;
	width = 1;
	height = 1;
	health = 15;
	activateCycle = 0;
	activateCD = 0;

	animUnit = AnimationUnit::createNew();
	animUnit->type = AnimType::gridDirdCracked;
	animUnit->depth = 1;
	animUnit->deltaX = 0;
	animUnit->deltaY = 0;
	animUnit->x = this->x;
	animUnit->y = this->y;
	animUnit->angle = 0;
	animUnit->flip = SDL_FLIP_NONE;
	animUnit->height = height * 32;
	animUnit->width = height * 32;
}

idea_facility_dirt_cracked::~idea_facility_dirt_cracked() = default;
