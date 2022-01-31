#include "GameToolkit.h"

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

void GameToolkit::getLengthUTF8(char const* str, int* cnt)
{
    while (*str != '\0') {
        if (*str & 1 << 7) {
            if (*str & (1 << 6)) {
                if (*str & (1 << 5)) {
                    if (*str & (1 << 4)) {
                        cnt[4]++; cnt[0]++; str += 4;
                        continue;
                    }
                    cnt[3]++; cnt[0]++; str += 3;
                    continue;
                }
                cnt[2]++; cnt[0]++; str += 2;
                continue;
            }
        }
        cnt[1]++; cnt[0]++; str += 1;
        continue;
    }
}

SDL_Texture* GameToolkit::getRenderedText(char const* str, SDL_Color color, int* width, int* height)
{
	int count_str[4] = { 0,0,0,0 };
	GameToolkit::getLengthUTF8(str, count_str);

	SDL_Surface* surface = TTF_RenderUTF8_Blended(RenderingSystem::getInstance()->font_zpix, str, color);

	SDL_Texture* _texture = SDL_CreateTextureFromSurface(GlobalData::sdl_renderer, surface);

	SDL_FreeSurface(surface);

	TTF_SizeUTF8(RenderingSystem::getInstance()->font_zpix, str, width, height);

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
