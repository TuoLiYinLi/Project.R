#include "RenderingText.h"

#include "GameToolkit.h"
#include "GlobalData.h"
#include "RenderingSystem.h"

RenderingText* RenderingText::createNew()
{
	return new RenderingText();
}

void RenderingText::setTexture(const wchar_t* unicode_str, double scale, SDL_Color color)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	int w, h;
	texture = GameToolkit::createUnicodeLine(unicode_str, color, &w, &h);

	width = w * scale;
	height = h * scale;
}

void RenderingText::setTexture(const wchar_t* unicode_str, double scale, SDL_Color color, SDL_Color bg_color)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	int w, h;
	texture = GameToolkit::createUnicodeLine(unicode_str, color, bg_color, &w, &h);

	width = w * scale;
	height = h * scale;
}



void RenderingText::setTexture(const wchar_t* unicode_str, double scale, SDL_Color color, int wrapLength)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	int w, h;
	texture = GameToolkit::createUnicodeText(unicode_str, color, wrapLength, &w, &h);

	width = w*scale;
	height = h*scale;
}

void RenderingText::setTexture(const wchar_t* unicode_str, double scale, SDL_Color color, SDL_Color bg_color, int wrapLength)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	int w, h;
	texture = GameToolkit::createUnicodeText(unicode_str, color, bg_color, wrapLength, &w, &h);

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

