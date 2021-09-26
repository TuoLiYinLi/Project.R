#include "FacilitySlimeGlue.h"
#include "Defined.h"
#include "GameToolkit.h"
FacilitySlimeGlue* FacilitySlimeGlue::createNew()
{
    auto sg = new FacilitySlimeGlue();
    return sg;
}

void FacilitySlimeGlue::destroy()
{
    delete this;
}

void FacilitySlimeGlue::onAnytime()
{

}

void FacilitySlimeGlue::onActivate()
{

	//std::cout << "\t\tFacilitySlimeGlue::onActivate()\n";

}

void FacilitySlimeGlue::onIdle()
{

	//std::cout << "\t\tFacilitySlimeGlue::onIdle()\n";

}

void FacilitySlimeGlue::onDeath()
{
}

void FacilitySlimeGlue::onHit(Form* form)
{
	//std::cout << this->health <<" FacilitySlimeGlue\n";
	health -= 1;
	if (health < 0) {
		health = 0;
	}
	gameToolkit::createText(x, y, "-1", { 255,255,255,255 });
}

AnimType FacilitySlimeGlue::getAnimType()
{
    return AnimType::faciSlimeGlue_L1;
}

FacilitySlimeGlue::FacilitySlimeGlue()
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

FacilitySlimeGlue::~FacilitySlimeGlue()
{
	std::cout << "FacilitySlimeGlue::~FacilitySlimeGlue()\n";
	if (counting != nullptr) 
	{
		counting->destroy();
	}
}
