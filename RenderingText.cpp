#include "RenderingText.h"

#include "GameToolkit.h"
#include "GlobalData.h"
#include "RenderingSystem.h"

RenderingText* RenderingText::createNew()
{
	return new RenderingText();
}

void RenderingText::setTexture(const char* utf8_msg, SDL_Color color, double scale)
{
	if(texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	int w, h;

	texture = GameToolkit::getRenderedText(utf8_msg, color, &w, &h);

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

