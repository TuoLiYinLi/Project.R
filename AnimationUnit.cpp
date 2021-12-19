#include "AnimationUnit.h"
#include "RenderingSystem.h"

AnimationUnit* AnimationUnit::createNew() {

	const auto au = new AnimationUnit();
	if (au == nullptr) {
#ifdef _DEBUG
		SDL_Log(u8"ERROR:new AnimationUnit()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr");
#endif // _DEBUG

	}
	return au;
}

void AnimationUnit::destroy() const{
	delete this;
}

AnimationUnit::AnimationUnit() {

	RenderingSystem::getInstance()->list_animation_units->push_back(this);

	current_num++;

	depth = 0;

	deltaX = 0;
	deltaY = 0;

	x = 0;
	y = 0;

	width = 32;
	height = 32;
	
	flip = false;

	texture = nullptr;
}

AnimationUnit::~AnimationUnit() {

	RenderingSystem::getInstance()->list_animation_units->remove(this);

	current_num--;
}

int AnimationUnit::current_num = 0;


int AnimationUnit::getCurrentNum() {
	return current_num;
}

void AnimationUnit::setFlip(bool _val)
{
	flip = _val;
}

SDL_RendererFlip AnimationUnit::getFlip() const
{
	if (flip)
	{
		return  SDL_FLIP_HORIZONTAL;
	}
	else
	{
		return  SDL_FLIP_NONE;
	}
}

void AnimationUnit::setTexture(AnimationType type, int time_length, int current)
{
	if (time_length == 0 || current == 0)
	{
		texture = RenderingSystem::getInstance()->list_animation_texture->at(int(type))->front();
		return;
	}

	const auto texture_num = (double)RenderingSystem::getInstance()->list_animation_texture->at((int)type)->size();
	const int animation_progress = (int)floor(texture_num * time_length / current);


	if (animation_progress >= texture_num) {
		SDL_Log(u8"ERROR:RenderingSystem::getTextureFromAU ³¬³ö·¶Î§");
	}

	texture = RenderingSystem::getInstance()->list_animation_texture->at(int(type))->at(animation_progress);
}


SDL_Texture* AnimationUnit::getTexture() const
{
	return texture;
}
