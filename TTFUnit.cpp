#include "TTFUnit.h"
#include "Defined.h"
void TTFUnit::set(double x, double y)
{
	world_x = x;
	world_y = y;
}
TTFUnit* TTFUnit::createNew(const char* _message, SDL_Color _color)
{
	auto ttf = new TTFUnit(_message, _color);
	return ttf;
}

void TTFUnit::destroy()
{
	delete this;
}

int TTFUnit::currentNum = 0;

int TTFUnit::getCurrentNum()
{
	return currentNum;
}

TTFUnit::TTFUnit(const char* _message, SDL_Color _color)
{
#ifdef TTF_UNIT_DEBUG
	std::cout << "\t\tTTFUnit::TTFUnit(const char* _message, SDL_Color _color)\n";
#endif // TTF_UNIT_DEBUG

	AnimSystem::getInstance()->fontUnitList->push_back(this);

	currentNum++;

	world_x = 0;
	world_y = 0;
	w = 0;
	h = 1;
	int count = 0;
	std::string s = _message;
	char _n = '\n';

	while (s[s.size() - 1] == _n) {
		s.erase(s.size() - 1, 1);
	}
	//s.push_back('\n');
	//std::cout << s << "\n";
	for (auto it = 0; it <s.size(); it++)
	{
		//std::cout <<count <<"\n";
		if (s[it] == _n) {
			//std::cout << count << "\n";
			if (w < count) {
				w = count;
			}
			h++;
			count = 0;
		}
		else
		{
			count++;
		}
		if (it == s.size() - 1&&w<count) {
			w = count;
		}
	}
	//s.erase(s.size() - 1, 1);
	
	std::cout <<"\t\tÄÚÈÝ[" << s.c_str() << "]\n";

	w *= FONT_PRECISION;
	h *= FONT_PRECISION;
	scale = 1;
	int length = std::string(_message).size();
	color = _color;
	depth = 300;
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(GlobalData::font, s.c_str(), color, w );
	texture = SDL_CreateTextureFromSurface(GlobalData::renderer, surface);
	SDL_FreeSurface(surface);
	if (h > FONT_PRECISION) {
		w *=1.635;
	}
}

TTFUnit::~TTFUnit()
{
#ifdef TTF_UNIT_DEBUG
	std::cout << "\t\tTTFUnit::~TTFUnit()\n";
#endif // TTF_UNIT_DEBUG
	SDL_DestroyTexture(texture);
	texture = nullptr;

	currentNum--;
}

