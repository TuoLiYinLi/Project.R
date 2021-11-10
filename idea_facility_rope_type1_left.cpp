#include "idea_facility_rope_type1_left.h"

idea_facility_rope_type1_left* idea_facility_rope_type1_left::createNew()
{
	return new idea_facility_rope_type1_left();
}

void idea_facility_rope_type1_left::destroy()
{
	delete this;
}

idea_facility_rope_type1_left::idea_facility_rope_type1_left()
{
	animUnit->flip = SDL_FLIP_HORIZONTAL;
}
