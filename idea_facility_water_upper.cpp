#include "idea_facility_water_upper.h"

idea_facility_water_upper* idea_facility_water_upper::createNew()
{
	auto f =new idea_facility_water_upper();
	return f;
}

void idea_facility_water_upper::destroy()
{
	delete this;
}

AnimType idea_facility_water_upper::getAnimType()
{
	return AnimType::gridWater_1upper;
}

idea_facility_water_upper::idea_facility_water_upper()
{
	tag = Tag::Water;

	blockingType = BlockingType::liquid;
	ally = AllyType::peace;
	idleLength = 0;
	activateLength = 0;
	deathLength = 0;
	width = 1;
	height = 1;
	health = 100;
	activateCycle = 0;
	activateCD = 0;

	animUnit = AnimationUnit::createNew();
	animUnit->type = AnimType::gridWater_1upper;
	animUnit->depth = 200;
	animUnit->deltaX = 0;
	animUnit->deltaY = 0;
	animUnit->x = this->x;
	animUnit->y = this->y;
	animUnit->angle = 0;
	animUnit->flip = SDL_FLIP_NONE;
	animUnit->height = height * 32;
	animUnit->width = height * 32;
}

idea_facility_water_upper::~idea_facility_water_upper()
{
}
