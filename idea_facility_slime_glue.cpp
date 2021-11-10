#include "idea_facility_slime_glue.h"
#include "Defined.h"
#include "GameToolkit.h"
idea_facility_slime_glue* idea_facility_slime_glue::createNew()
{
    auto sg = new idea_facility_slime_glue();
    return sg;
}

void idea_facility_slime_glue::destroy()
{
    delete this;
}

void idea_facility_slime_glue::onAnytime()
{

}

void idea_facility_slime_glue::onActivate()
{

	//std::cout << "\t\tFacilitySlimeGlue::onActivate()\n";

}

void idea_facility_slime_glue::onIdle()
{

	//std::cout << "\t\tFacilitySlimeGlue::onIdle()\n";

}

void idea_facility_slime_glue::onDeath()
{
}

void idea_facility_slime_glue::onHit(Form* form)
{
	//std::cout << this->health <<" idea_facility_slime_glue\n";
	health -= 1;
	if (health < 0) {
		health = 0;
	}
	gameToolkit::createText(x, y, "-1", { 255,255,255,255 });
}

AnimType idea_facility_slime_glue::getAnimType()
{
    return AnimType::faciSlimeGlue_L1;
}

idea_facility_slime_glue::idea_facility_slime_glue()
{
	blockingType = BlockingType::no;
	ally = AllyType::ally;
	idleLength = 0;
	activateLength = 0;
	deathLength = 0;
	width = 1;
	height = 1;
	health = 12;
	activateCycle = 0;
	activateCD = 0;

	animUnit = AnimationUnit::createNew();

	animUnit->type = AnimType::faciSlimeGlue_L1;
	animUnit->depth = 1;
	animUnit->deltaX = 0;
	animUnit->deltaY = 0;
	animUnit->x = this->x;
	animUnit->y = this->y;
	animUnit->angle = 0;
	animUnit->flip = SDL_FLIP_NONE;
	animUnit->height = height * 32;
	animUnit->width = height * 32;

	counting = Counting::createNew();
	counting->addNumOf(CountingType::slimeGlue, 2);
}

idea_facility_slime_glue::~idea_facility_slime_glue()
{
	std::cout << "idea_facility_slime_glue::~idea_facility_slime_glue()\n";
	if (counting != nullptr) 
	{
		counting->destroy();
	}
}
