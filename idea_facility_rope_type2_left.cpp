#include "idea_facility_rope_type2_left.h"

idea_facility_rope_type2_left* idea_facility_rope_type2_left::createNew()
{
    return new idea_facility_rope_type2_left();
}

void idea_facility_rope_type2_left::destroy()
{
    delete this;
}

idea_facility_rope_type2_left::idea_facility_rope_type2_left()
{
	animUnit->type = AnimType::rope2;
	animUnit->flip = SDL_FLIP_HORIZONTAL;
}
