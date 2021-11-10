#include "idea_facility_rope_head_left.h"

idea_facility_rope_head_left* idea_facility_rope_head_left::createNew()
{
    return new idea_facility_rope_head_left();
}

void idea_facility_rope_head_left::destroy()
{
    delete this;
}

idea_facility_rope_head_left::idea_facility_rope_head_left()
{
    animUnit->flip = SDL_FLIP_HORIZONTAL; 
}

idea_facility_rope_head_left::~idea_facility_rope_head_left()
{
}
