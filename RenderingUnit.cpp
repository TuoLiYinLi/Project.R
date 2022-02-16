#include "RenderingUnit.h"
#include "RenderingSystem.h"


RenderingUnit* RenderingUnit::createNew()
{
	const auto ru = new RenderingUnit();
#ifdef _DEBUG
	if (ru == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"new RenderingUnit()申请内存失败，值为nullptr");
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
	
	clipping_rect = nullptr;
}

RenderingUnit::~RenderingUnit() {

	RenderingSystem::getInstance()->remove(this);

	rendering_unit_num--;

	
	delete clipping_rect;
	clipping_rect = nullptr;
	
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
#ifdef _DEBUG
	if(texture==nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"从RenderingUnit::getTexture()获取了空的材质");
	}
#endif

	return this->texture;
}

int RenderingUnit::rendering_unit_num = 0;

int RenderingUnit::getRenderingUnitNum()
{
	return  rendering_unit_num;
}

void RenderingUnit::setClipping(int _x, int _y, int _w, int _h)
{
	delete clipping_rect;
	clipping_rect = new SDL_Rect({ _x, _y, _w, _h });
}
