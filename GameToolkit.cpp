#include "GameToolkit.h"
#include <random>
#include "Defined.h"
#include "GlobalData.h"
#include "PhysicsChara.h"
#include "RenderingSystem.h"
#include "UISystem.h"
#include "WorldSystem.h"
#include "PhysicsFacility.h"

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
	const std::wstring s = std::to_wstring(d);
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

bool GameToolkit::boolOverride(bool ori, OverrideOperation operation)
{
	switch (operation) {
	case OverrideOperation::override_false: return false;
	case OverrideOperation::override_true: return true;
	case OverrideOperation::stay_original: return ori;
	}

#ifdef _DEBUG
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"boolOverride发生不可思议");
	return false;
#endif
}

std::list<Chara*> GameToolkit::findCharaIn(AllyType ally, int x, int y)
{
	auto out = std::list<Chara*>();
	const auto g = WorldSystem::getInstance()->getGrid(x, y);
	if (!g)return out;
	for (auto i = g->list_physics_chara->begin(); i !=g->list_physics_chara->end(); ++i)
	{
		if((*i)->type_ally==ally)
		{
			out.push_back(reinterpret_cast<Chara*>((*i)->game_object));
		}
	}
	return out;
}

std::list<Chara*> GameToolkit::findCharaInArea(AllyType ally, int x, int y, int w, int h)
{
	auto out = std::list<Chara*>();

	for (int X = x; X < x + w; ++X)
	{
		for (int Y = y; Y < y + h; ++Y)
		{
			out.splice(out.end(), findCharaIn(ally, X, Y));
		}
	}
	return out;
}

std::list<Facility*> GameToolkit::findFacilityIn(FacilityType type, int x, int y)
{
	auto out = std::list<Facility*>();
	const auto g = WorldSystem::getInstance()->getGrid(x, y);
	if (!g)return out;
	for (auto i = g->list_physics_facility->begin(); i != g->list_physics_facility->end(); ++i)
	{
		auto f = reinterpret_cast<Facility*>((*i)->game_object);
		if (f->type_facility==type)
		{
			out.push_back(f);
		}
	}
	return out;
}

std::list<Facility*> GameToolkit::findFacilityInArea(FacilityType type, int x, int y, int w, int h)
{
	auto out = std::list<Facility*>();

	for (int X = x; X <= x + w; ++X)
	{
		for (int Y = y; Y <= y + h; ++Y)
		{
			out.splice(out.end(), findFacilityIn(type, X, Y));
		}
	}
	return out;
}

bool GameToolkit::findBlockingIn(BlockingType blocking, int x, int y)
{
	const auto g = WorldSystem::getInstance()->getGrid(x, y);
	if (!g)return false;
	return g->getBlockingType(blocking);
}

bool GameToolkit::findBlockingInArea(BlockingType blocking, int x, int y, int w, int h)
{
	for (int X = x; X < x + w; ++X)
	{
		for (int Y = y; Y < y + h; ++Y)
		{
			if(findBlockingIn(blocking, X, Y))
			{
				return true;
			}
		}
	}
	return false;
}

double GameToolkit::getDistance(PhysicsObject* p1, PhysicsObject* p2)
{
	double x_distance;
	if (p1->X + p1->bodyX * 0.5 > p2->X + p2->bodyX * 0.5)
	{
		x_distance = p1->getLeft() - p2->getRight();
	}
	else
	{
		x_distance = p2->getLeft() - p1->getRight();
	}

	if (x_distance<0)
	{
		x_distance = 0;
	}

	double y_distance;
	if (p1->Y + p1->bodyY * 0.5 > p2->Y + p2->bodyY * 0.5)
	{
		y_distance = p2->getUp() - p1->getDown();
	}
	else
	{
		y_distance = p1->getUp() - p2->getDown();
	}

	if(y_distance<0)
	{
		y_distance = 0;
	}

	return x_distance + y_distance;
}
