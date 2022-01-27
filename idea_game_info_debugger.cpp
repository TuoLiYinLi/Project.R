#include <string>
#include "idea_game_info_debugger.h"

#include "Defined.h"
#include "GameToolkit.h"
#include "GlobalData.h"

idea_game_info_debugger* idea_game_info_debugger::createNew()
{
	const auto ru = new idea_game_info_debugger();
	if (ru == nullptr) {
#ifdef _DEBUG
		SDL_Log(u8"警告 new idea_physics_debugger()申请内存失败，值为nullptr");
#endif // _DEBUG

	}
	return ru;
}

void idea_game_info_debugger::update()
{
	renew_texture();
}

idea_game_info_debugger::idea_game_info_debugger()
{
	name = "game_info_debugger";

	animation_unit = RenderingUnit::createNew();
	animation_unit->deltaX = 0;
	animation_unit->deltaY = 0;
	animation_unit->width = WINDOW_WIDTH;
	animation_unit->height = WINDOW_HEIGHT;
	animation_unit->reference = RenderingReference::window;
	animation_unit->depth = RENDERING_DEPTH_EXTRA + 2;
	create_texture();
	renew_texture();
}

idea_game_info_debugger::~idea_game_info_debugger()
{
	destroy_texture();
}

void idea_game_info_debugger::renew_texture() const
{
	SDL_SetRenderTarget(GlobalData::sdl_renderer, animation_unit->getTexture());
	//渲染为完全透明
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(GlobalData::sdl_renderer, nullptr);

	render_text();
}

void idea_game_info_debugger::create_texture() const
{
	SDL_Texture* texture = SDL_CreateTexture(GlobalData::sdl_renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		WINDOW_WIDTH, WINDOW_HEIGHT);

	animation_unit->setTexture(texture);
	SDL_SetTextureBlendMode(animation_unit->getTexture(), SDL_BLENDMODE_BLEND);
}

void idea_game_info_debugger::destroy_texture() const
{
	//手动销毁材质
	if (animation_unit->getTexture())
	{
		SDL_DestroyTexture(animation_unit->getTexture());
		animation_unit->setTexture(nullptr);
	}
}

void idea_game_info_debugger::render_text() const
{
	const std::string msg = u8"physics frame:" + std::to_string(GlobalData::getTimePhysicsFrames());
	SDL_Rect rect = { 0,0,0,0 };
	SDL_Texture* text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);

	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);

	SDL_DestroyTexture(text);
}
