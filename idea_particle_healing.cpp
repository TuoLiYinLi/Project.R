#include "idea_particle_healing.h"

idea_particle_healing* idea_particle_healing::createNew()
{
	return new idea_particle_healing();
}

idea_particle_healing::idea_particle_healing()
{
	width = 6;
	height = 6;
	x_center = 3;
	y_center = 3;
	scale = 1;

	//…Ë÷√∂Øª≠
	animation = AnimationType::particle_healing;
	animation_progress = 0;
	animation_length = 40;
	life_time = 40;

	update_position();
	sync_animation();
}
