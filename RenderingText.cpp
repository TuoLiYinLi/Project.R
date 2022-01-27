#include "RenderingText.h"

#include "GameToolkit.h"
#include "GlobalData.h"
#include "RenderingSystem.h"

RenderingText* RenderingText::createNew()
{
	const auto rt = new RenderingText();
	if (rt == nullptr) {
#ifdef _DEBUG
		SDL_Log(u8"ERROR:new RenderingAnimation()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr");
#endif // _DEBUG

	}
	return rt;
}

void RenderingText::setTexture(const char* utf8_msg, SDL_Color color, double scale)
{
	if(texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	int count_str[4] = { 0,0,0,0 };
	GameToolkit::getLengthUTF8(utf8_msg, count_str);

	SDL_Surface* surface = TTF_RenderUTF8_Blended(RenderingSystem::getInstance()->font_zpix, utf8_msg, color);

	SDL_Texture* _texture = SDL_CreateTextureFromSurface(GlobalData::sdl_renderer, surface);

	SDL_FreeSurface(surface);

	texture = _texture;

	int w, h;

	TTF_SizeUTF8(RenderingSystem::getInstance()->font_zpix, utf8_msg, &w, &h);

	width = w * scale;
	height = h * scale;
}


RenderingText::RenderingText()
{
	
}

RenderingText::~RenderingText()
{
	if(texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

