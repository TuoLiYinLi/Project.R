#include "idea_particle_goldust.h"

idea_particle_goldust* idea_particle_goldust::createNew()
{
	return new idea_particle_goldust();
}

idea_particle_goldust::idea_particle_goldust()
{
	width = 13;
	height = 13;
	x_center = 6.5;
	y_center = 6.5;
	scale = 1;

	//…Ë÷√∂Øª≠
	animation = AnimationType::particle_goldust;
	animation_progress = 0;
	animation_length = 60;
	life_time = 60;

	update_position();
	sync_animation();
}