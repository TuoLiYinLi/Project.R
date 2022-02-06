#include "RenderingAnimation.h"
#include "RenderingSystem.h"

RenderingAnimation* RenderingAnimation::createNew()
{
	return new RenderingAnimation();
}

RenderingAnimation::RenderingAnimation() {

}

RenderingAnimation::~RenderingAnimation() {

}

void RenderingAnimation::setTexture(AnimationType type, int time_length, int current)
{
	if (time_length == 0 || current == 0)
	{
		texture = RenderingSystem::getInstance()->getAnimation(type, 0);
		return;
	}

	const auto texture_num = static_cast<double>(RenderingSystem::getInstance()->getAnimationSize(type));
	const int animation_progress = static_cast<int>(floor(texture_num * current / time_length));

#ifdef _DEBUG
	if (animation_progress >= texture_num) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR,u8"RenderingSystem::getTextureFromAU ³¬³ö·¶Î§ progress:%d num:%d",animation_progress,static_cast<int>(texture_num));
	}
#endif

	texture = RenderingSystem::getInstance()->getAnimation(type, animation_progress);
}

