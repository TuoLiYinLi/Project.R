#include "RenderingUnit.h"

#include "RenderingSystem.h"


RenderingUnit* RenderingUnit::createNew()
{
	const auto ru = new RenderingUnit();
	if (ru == nullptr) {
#ifdef _DEBUG
		SDL_Log(u8"���� new RenderingUnit()�����ڴ�ʧ�ܣ�ֵΪnullptr");
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
		SDL_Log(u8"���� �����µĲ���ʱû������ԭ�в���");
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

bool RenderingUnit::operator<(RenderingUnit* ru)
{
	return this->depth < ru->depth;
}

