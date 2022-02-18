#include "idea_particle_poisoned.h"

#include "GameToolkit.h"

idea_particle_poisoned* idea_particle_poisoned::createNew()
{
	return new idea_particle_poisoned();
}

void idea_particle_poisoned::update()
{
	y_v *= 0.98;
	x_v = x_range * cos(life_time * 0.06 + t_phase);
	Particle::update();
}


idea_particle_poisoned::idea_particle_poisoned()
{
	t_phase = GameToolkit::random(-3.14159, 3.14159);
	x_range = 0.006;
	y_v = -0.02;
	width = 8;
	height = 8;
	x_center = 4;
	y_center = 4;
	scale = 1;

	//…Ë÷√∂Øª≠
	animation = AnimationType::particle_poisoned;
	animation_progress = 0;
	animation_length = 60;
	life_time = 60;

	update_position();
	sync_animation();
}

