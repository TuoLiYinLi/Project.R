#include <string>
#include "idea_game_info_debugger.h"

#include "Chara.h"
#include "Defined.h"
#include "Facility.h"
#include "GameToolkit.h"
#include "GlobalData.h"
#include "Monster.h"
#include "PhysicsFacility.h"
#include "PhysicsProjectile.h"
#include "Projectile.h"
#include "UISystem.h"
#include "Warrior.h"
#include "WorldSystem.h"

idea_game_info_debugger* idea_game_info_debugger::createNew()
{
	const auto ru = new idea_game_info_debugger();
	if (ru == nullptr) {
#ifdef _DEBUG
		SDL_Log(u8"警告 new idea_game_info_debugger()申请内存失败，值为nullptr");
#endif // _DEBUG

	}
	return ru;
}

void idea_game_info_debugger::update()
{
	if(GlobalData::flag_debug_game_info)
	{
		renew_texture();
		animation_unit->flag_enable = true;
	}else
	{
		animation_unit->flag_enable = false;
	}
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
	std::string msg = u8"physics frame:" + std::to_string(GlobalData::getTimePhysicsFrames());
	SDL_Rect rect = { 0,0,0,0 };

	SDL_Texture* text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	SDL_DestroyTexture(text);

	msg = +u8"RenderingUnit:" + std::to_string(RenderingUnit::getRenderingUnitNum())
		+ u8" Grid:" + std::to_string(Grid::getGridNum());
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	SDL_DestroyTexture(text);

	msg = u8"GameObjectNum: <Total:" + std::to_string(GameObject::getGameObjectNum())
		+ u8"> <Character:" + std::to_string(Chara::getCharaNum())
		+ u8"> <Facility:" + std::to_string(Facility::getFacilityNum())
		+ u8"> <Projectile:" + std::to_string(Projectile::getProjectileNum())
		+ u8">";
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	SDL_DestroyTexture(text);

	msg = + u8"PhysicsNum: <Object:" + std::to_string(PhysicsObject::getPhysicsObjectNum())
		+ u8"> <Character:" + std::to_string(PhysicsChara::getPhysicsCharaNum())
		+ u8"> <Facility:" + std::to_string(PhysicsFacility::getPhysicsFacillityNum())
		+ u8"> <Projectile:" + std::to_string(PhysicsProjectile::getPhysicsProjectilleNum())
		+ u8">";
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	SDL_DestroyTexture(text);


	const int grid_x = (int)floor(UISystem::getInstance()->mouseX_world);
	const int grid_y = (int)floor(UISystem::getInstance()->mouseY_world);
	msg = u8"GridAt:(" + std::to_string(grid_x) + u8","
		+ std::to_string(grid_y) + u8")";
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	SDL_DestroyTexture(text);

	const auto g= WorldSystem::getInstance()->getGrid(grid_x, grid_y);

	if(g==nullptr)
	{
		msg = u8"Outside Grid";
		rect.y += rect.h;
		text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
		SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
		SDL_DestroyTexture(text);
	}else
	{
		msg = u8"CharaNum:" + std::to_string(g->list_physics_chara->size())
			+ u8" FacilityNum:" + std::to_string(g->list_physics_facility->size())
			+ u8" ProjectileNum:" + std::to_string(g->list_physics_projectile->size());
		rect.y += rect.h;
		text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
		SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
		SDL_DestroyTexture(text);
	}
	msg = u8"EnemyNum:" + std::to_string(Warrior::getWarriorNum())
		+ u8" MonsterNum:" + std::to_string(Monster::getMonsterNum());
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	SDL_DestroyTexture(text);

	msg = u8"EnemyWaveNum:" + std::to_string(WorldSystem::getInstance()->enemy_wave_num)
		+ u8" EnemyWaveCD:" + std::to_string(WorldSystem::getInstance()->enemy_wave_CD)
		+ u8" GoldustEnergy:" + std::to_string((int)WorldSystem::getInstance()->goldust_energy);
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	SDL_DestroyTexture(text);

	msg = u8"TimeSpeed:" + std::to_string((int)GlobalData::getTimeSpeed())
		+ u8" TimePause:" + std::to_string(GlobalData::flag_stop);
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	SDL_DestroyTexture(text);
}
