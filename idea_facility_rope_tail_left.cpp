#include "idea_facility_rope_tail_left.h"

idea_facility_rope_tail_left* idea_facility_rope_tail_left::createNew()
{
    return new idea_facility_rope_tail_left();
}

void idea_facility_rope_tail_left::destroy()
{
    delete this;
}

idea_facility_rope_tail_left::idea_facility_rope_tail_left()
{
    animUnit->flip = SDL_FLIP_HORIZONTAL;
    animUnit->type=AnimType::ropeTail;
}
