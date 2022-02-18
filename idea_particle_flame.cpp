#include "idea_particle_flame.h"

idea_particle_flame* idea_particle_flame::createNew()
{
	return new idea_particle_flame();
}

idea_particle_flame::idea_particle_flame()
{
	width = 8;
	height = 8;
	x_center = 4;
	y_center = 6;
	scale = 1;

	//…Ë÷√∂Øª≠
	animation = AnimationType::particle_flame;
	animation_progress = 0;
	animation_length = 80;
	life_time = 80;

	update_position();
	sync_animation();
}

void idea_particle_flame::update()
{
	y_v -= 0.00025;
	Particle::update();
}
