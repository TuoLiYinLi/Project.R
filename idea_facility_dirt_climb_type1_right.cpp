#include "idea_facility_dirt_climb_type1_right.h"

idea_facility_dirt_climb_type1_right* idea_facility_dirt_climb_type1_right::createNew()
{
    return new idea_facility_dirt_climb_type1_right();
}

void idea_facility_dirt_climb_type1_right::destroy()
{
    delete this;
}

idea_facility_dirt_climb_type1_right::idea_facility_dirt_climb_type1_right()
{
    animUnit->flip = SDL_FLIP_HORIZONTAL;
}

