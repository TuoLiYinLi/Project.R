#include "GameToolkit.h"
#include <random>
#include "Defined.h"
#include "GlobalData.h"
#include "RenderingSystem.h"
#include "UISystem.h"

void GameToolkit::transPositionWorldToWindow(double x_world, double y_world, double* x_window, double* y_window)
{
	const RenderingSystem* a = RenderingSystem::getInstance();
	const double k = a->viewScale / 0.03125;
	*x_window = (x_world - a->viewX - 0.015625 * WINDOW_WIDTH) * k + 0.5 * WINDOW_WIDTH;
	*y_window = (y_world - a->viewY - 0.015625 * WINDOW_HEIGHT) * k + 0.5 * WINDOW_HEIGHT;
}

void GameToolkit::transPositionWindowToWorld(double x_window, double y_window, double* x_world, double* y_world)
{
	const RenderingSystem* a = RenderingSystem::getInstance();
	const double k = 0.03125 / a->viewScale;
	*x_world = a->viewX + 0.015625 * WINDOW_WIDTH
	+ k * (x_window - 0.5 * WINDOW_WIDTH);
	*y_world = a->viewY + 0.015625 * WINDOW_HEIGHT
	+ k * (y_window - 0.5 * WINDOW_HEIGHT);
}

SDL_Texture* GameToolkit::createUnicodeLine(const wchar_t* unicode_str, SDL_Color color, int* width, int* height)
{
	const auto str = reinterpret_cast<Uint16*>(const_cast<wchar_t*>(unicode_str));

	SDL_Surface* surface = TTF_RenderUNICODE_Solid(RenderingSystem::getInstance()->font_grey, str, color);

	if(width)*width = surface->w;
	if(height)*height = surface->h;

	SDL_Texture* _texture = SDL_CreateTextureFromSurface(GlobalData::sdl_renderer, surface);

	SDL_FreeSurface(surface);

	return _texture;
}

SDL_Texture* GameToolkit::createUnicodeLine(const wchar_t* unicode_str, SDL_Color color, SDL_Color bg_color, int* width, int* height)
{
	const auto str = reinterpret_cast<Uint16*>(const_cast<wchar_t*>(unicode_str));

	SDL_Surface* surface = TTF_RenderUNICODE_Shaded(RenderingSystem::getInstance()->font_grey, str, color,bg_color);

	if (width)*width = surface->w;
	if (height)*height = surface->h;

	SDL_Texture* _texture = SDL_CreateTextureFromSurface(GlobalData::sdl_renderer, surface);

	SDL_FreeSurface(surface);

	return _texture;
}


SDL_Texture* GameToolkit::createUnicodeText(const wchar_t* unicode_str, SDL_Color color, int wrapLength, int* w, int* h)
{
	const auto str = reinterpret_cast<Uint16*>(const_cast<wchar_t*>(unicode_str));

	//int extent;
	//TTF_MeasureUNICODE(RenderingSystem::getInstance()->font_grey, str, wrapLength, &extent,nullptr);

	SDL_Surface* surface = TTF_RenderUNICODE_Solid_Wrapped(RenderingSystem::getInstance()->font_grey, str, color, wrapLength);

	if (w)*w = surface->w;
	if (h)*h = surface->h;

	SDL_Texture* _texture = SDL_CreateTextureFromSurface(GlobalData::sdl_renderer, surface);
	SDL_FreeSurface(surface);

	return _texture;
}

SDL_Texture* GameToolkit::createUnicodeText(const wchar_t* unicode_str, SDL_Color color, SDL_Color bg_color, int wrapLength, int* w, int* h)
{
	const auto str = reinterpret_cast<Uint16*>(const_cast<wchar_t*>(unicode_str));

	//int extent;
	//TTF_MeasureUNICODE(RenderingSystem::getInstance()->font_grey, str, wrapLength, &extent, nullptr);

	SDL_Surface* surface = TTF_RenderUNICODE_Shaded_Wrapped(RenderingSystem::getInstance()->font_grey, str, color, bg_color, wrapLength);

	if (w)*w = surface->w;
	if (h)*h = surface->h;

	SDL_Texture* _texture = SDL_CreateTextureFromSurface(GlobalData::sdl_renderer, surface);
	SDL_FreeSurface(surface);

	return _texture;
}


bool GameToolkit::checkIfHostile(AllyType _t1, AllyType _t2)
{
	if (_t1 == AllyType::peace || _t2 == AllyType::peace)return false;
	if (_t1 == _t2)return false;
	return true;
}

int GameToolkit::getWaveTime(int t)
{
	if(t<=0)
	{
		return 0;
	}else if (t==1)
	{
		return 60 * 60 * 6;
	}else if (t==2)
	{
		return 60 * 60 * 4;
	}else if (t==3)
	{
		return 60 * 60 * 3;
	}
	else
		return 60 * 60 * 2;
		
}

bool GameToolkit::checkMouseInRange(int _x1, int _y1, int _x2, int _y2)
{
	const auto u= UISystem::getInstance();
	return u->mouseX_window >= _x1 && u->mouseX_window <= _x2
		&& u->mouseY_window >= _y1 && u->mouseY_window <= _y2;
}

std::wstring GameToolkit::double_reserve_decimal(double d, int n)
{
	std::wstring s = std::to_wstring(d);
	const auto find = s.find_first_of(L'.');
	return s.substr(0, find + n + 1);
}

double GameToolkit::random(double min, double max)
{
	std::random_device rd;
	return static_cast<double>(rd()) / std::random_device::max() * (max - min) + min;
}

unsigned GameToolkit::random(unsigned range)
{
	if (range == 0)return 0;
	std::random_device rd;
	return static_cast<int>(rd()) % range;
}
