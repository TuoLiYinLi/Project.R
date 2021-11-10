#include "idea_facility_ladder_right.h"

idea_facility_ladder_right* idea_facility_ladder_right::createNew()
{
	auto f = new idea_facility_ladder_right();
	return f;
}

void idea_facility_ladder_right::destroy()
{
	delete this;
}

AnimType idea_facility_ladder_right::getAnimType()
{
	return AnimType::ladder;
}

idea_facility_ladder_right::idea_facility_ladder_right()
{
	animUnit->flip = SDL_FLIP_HORIZONTAL;
	animUnit->type = AnimType::ladder;
}

idea_facility_ladder_right::~idea_facility_ladder_right()
{
}
