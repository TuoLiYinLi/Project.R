#include "RenderingUnit.h"
#include "RenderingSystem.h"


RenderingUnit* RenderingUnit::createNew()
{
	const auto ru = new RenderingUnit();
#ifdef _DEBUG
	if (ru == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"new RenderingUnit()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr");
	}
#endif // _DEBUG
	return ru;
}

void RenderingUnit::destroy() const {
	delete this;
}

RenderingUnit::RenderingUnit()
{
	rendering_unit_num++;

	RenderingSystem::getInstance()->add(this);

	flag_enable = true;

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

	RenderingSystem::getInstance()->remove(this);

	rendering_unit_num--;
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
		texture = nullptr;
	}
	texture = _texture;
}

SDL_Texture* RenderingUnit::getTexture() const
{
	return texture;
}

int RenderingUnit::rendering_unit_num = 0;

int RenderingUnit::getRenderingUnitNum()
{
	return  rendering_unit_num;
}

