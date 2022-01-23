#include "RenderingUnit.h"

#include "RenderingSystem.h"


RenderingUnit* RenderingUnit::createNew()
{
	const auto ru = new RenderingUnit();
	if (ru == nullptr) {
#ifdef _DEBUG
		SDL_Log(u8"警告 new RenderingUnit()申请内存失败，值为nullptr");
#endif // _DEBUG

	}
	return ru;
}

void RenderingUnit::destroy() const {
	delete this;
}

RenderingUnit::RenderingUnit()
{
	RenderingSystem::getInstance()->list_rendering_units->push_back(this);

	current_num++;

	reference = RenderingReference::world;

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

RenderingUnit::~RenderingUnit() {

	RenderingSystem::getInstance()->list_rendering_units->remove(this);

	current_num--;

	if(this->texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

}

void RenderingUnit::setFlip(bool _val)
{
	flip = _val;
}


SDL_RendererFlip RenderingUnit::getFlip() const
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

void RenderingUnit::setTexture(SDL_Texture* _texture)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		SDL_Log(u8"警告 在设置新的材质时销毁原有材质");
	}
	texture = _texture;
}

SDL_Texture* RenderingUnit::getTexture() const
{
	return texture;
}

int RenderingUnit::current_num = 0;

int RenderingUnit::getCurrentNum()
{
	return  current_num;
}
