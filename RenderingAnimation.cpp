#include "RenderingAnimation.h"
#include "RenderingSystem.h"

RenderingAnimation* RenderingAnimation::createNew() {

	const auto au = new RenderingAnimation();
	if (au == nullptr) {
#ifdef _DEBUG
		SDL_Log(u8"ERROR:new RenderingAnimation()�����ڴ�ʧ�ܣ�ֵΪnullptr");
#endif // _DEBUG

	}
	return au;
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

	const auto texture_num = (double)RenderingSystem::getInstance()->getAnimationSize(type);
	const int animation_progress = (int)floor(texture_num * current / time_length);


	if (animation_progress >= texture_num) {
		SDL_Log(u8"ERROR:RenderingSystem::getTextureFromAU ������Χ progress:%d num:%d",animation_progress,(int)texture_num);
	}

	texture = RenderingSystem::getInstance()->getAnimation(type, animation_progress);
}

