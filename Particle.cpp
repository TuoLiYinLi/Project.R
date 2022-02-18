#include "Particle.h"
#include "Defined.h"
#include "RenderingSystem.h"

Particle* Particle::createNew()
{
	return new Particle();
}

void Particle::update()
{
	life_time--;
	if (life_time <= 0)
	{
		readyToDestroy();
		return;
	}
	rendering_unit->x += x_v;
	rendering_unit->y += y_v;
	update_position();
	if (animation_progress >= animation_length)
	{
		animation_progress = 0;
	}
	sync_animation();
	animation_progress++;
}


Particle::Particle()
{
	x_v = 0;
	y_v = 0;
	height = 16;
	width = 16;
	x_center = 0;
	y_center = 0;
	scale = 1;
	

	//ÉèÖÃ¶¯»­
	rendering_unit = RenderingAnimation::createNew();

	animation = AnimationType::debug_sequence_blue;
	animation_progress = 0;
	animation_length = 60;
	life_time = 60;

	rendering_unit->depth = depth_world_particle;

	update_position();
	sync_animation();
}

Particle::~Particle()
{
	rendering_unit->destroy();
	rendering_unit = nullptr;
}

void Particle::sync_animation() const
{
	reinterpret_cast<RenderingAnimation*>(rendering_unit)->setTexture(animation, animation_length, animation_progress);
}

void Particle::update_position() const
{
	rendering_unit->width = width * scale;
	rendering_unit->height = height * scale;
	rendering_unit->deltaX = -x_center * scale;
	rendering_unit->deltaY = -y_center * scale;
}
