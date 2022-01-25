#include "RenderingAnimation.h"
#include "RenderingSystem.h"

RenderingAnimation* RenderingAnimation::createNew() {

	const auto au = new RenderingAnimation();
	if (au == nullptr) {
#ifdef _DEBUG
		SDL_Log(u8"ERROR:new RenderingAnimation()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr");
#endif // _DEBUG

	}
	return au;
}

RenderingAnimation::RenderingAnimation() {

	deltaX = 0;
	deltaY = 0;
}

RenderingAnimation::~RenderingAnimation() {

	RenderingSystem::getInstance()->list_rendering_units->remove(this);

	current_num--;
}

void RenderingAnimation::setTexture(AnimationType type, int time_length, int current)
{
	if (time_length == 0 || current == 0)
	{
		texture = RenderingSystem::getInstance()->list_animation_texture->at(int(type))->front();
		return;
	}

	const auto texture_num = (double)RenderingSystem::getInstance()->list_animation_texture->at((int)type)->size();
	const int animation_progress = (int)floor(texture_num * current / time_length);


	if (animation_progress >= texture_num) {
		SDL_Log(u8"ERROR:RenderingSystem::getTextureFromAU ³¬³ö·¶Î§ progress:%d num:%d",animation_progress,texture_num);
	}

	texture = RenderingSystem::getInstance()->list_animation_texture->at(int(type))->at(animation_progress);
}

