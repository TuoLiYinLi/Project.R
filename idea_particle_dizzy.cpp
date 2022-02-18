#include "idea_particle_dizzy.h"

idea_particle_dizzy* idea_particle_dizzy::createNew()
{
	return new idea_particle_dizzy();
}

void idea_particle_dizzy::update()
{
	y_v -= 0.0001;
	rendering_unit->blend_color.a -= 2;
	Particle::update();
}

idea_particle_dizzy::idea_particle_dizzy()
{
	width = 8;
	height = 8;
	x_center = 4;
	y_center = 6;
	scale = 2;

	//…Ë÷√∂Øª≠
	animation = AnimationType::particle_dizzy;
	animation_progress = 0;
	animation_length = 40;
	life_time = 120;

	update_position();
	sync_animation();
}
