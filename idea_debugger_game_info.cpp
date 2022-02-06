#include <string>
#include "idea_debugger_game_info.h"

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

idea_debugger_game_info* idea_debugger_game_info::createNew()
{
	return new idea_debugger_game_info();
}

void idea_debugger_game_info::updateOnRendering()
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

idea_debugger_game_info::idea_debugger_game_info()
{
	name = u8"game_info_debugger";

	animation_unit = RenderingUnit::createNew();
	animation_unit->deltaX = 0;
	animation_unit->deltaY = 0;
	animation_unit->width = WINDOW_WIDTH;
	animation_unit->height = WINDOW_HEIGHT;
	animation_unit->reference = RenderingReference::window;
	animation_unit->depth = RENDERING_DEPTH_EXTRA + 2;

	last_text_textures = new std::list<SDL_Texture*>();

	create_texture();
	renew_texture();
}

idea_debugger_game_info::~idea_debugger_game_info()
{
	destroy_texture();

	delete last_text_textures;
}

void idea_debugger_game_info::renew_texture() const
{

	SDL_SetRenderTarget(GlobalData::sdl_renderer, animation_unit->getTexture());
	//渲染为完全透明
	SDL_SetRenderDrawBlendMode(GlobalData::sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 0, 0, 0, 0);
	SDL_RenderClear(GlobalData::sdl_renderer);

	//渲染鼠标位置
	const int _x= UISystem::getInstance()->mouseX_window;
	const int _y = UISystem::getInstance()->mouseY_window;
	
	SDL_SetRenderDrawColor(GlobalData::sdl_renderer, 255, 0, 0, 120);
	SDL_RenderDrawLine(GlobalData::sdl_renderer,0, _y, WINDOW_WIDTH, _y);
	SDL_RenderDrawLine(GlobalData::sdl_renderer, _x, 0, _x, WINDOW_HEIGHT);

	render_text();
}

void idea_debugger_game_info::create_texture() const
{
	SDL_Texture* texture = SDL_CreateTexture(GlobalData::sdl_renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	animation_unit->setTexture(texture);
}

void idea_debugger_game_info::destroy_texture() const
{
	//手动销毁材质
	if (animation_unit->getTexture())
	{
		SDL_DestroyTexture(animation_unit->getTexture());
		animation_unit->setTexture(nullptr);
	}
}

void idea_debugger_game_info::render_text() const
{
	for (auto i = last_text_textures->begin(); i != last_text_textures->end(); ++i)
	{
		SDL_DestroyTexture(*i);
	}
	last_text_textures->clear();

	std::string msg = u8"physics frame:" + std::to_string(GlobalData::getTimePhysicsFrames())
		+ u8" FPS:" + std::to_string(GlobalData::getFPS())
		+ u8" delta:" + std::to_string(GlobalData::getTimeDelta());
	SDL_Rect rect = { 0,0,0,0 };

	SDL_Texture* text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	last_text_textures->push_back(text);

	msg = +u8"RenderingUnit:" + std::to_string(RenderingUnit::getRenderingUnitNum())
		+ u8" Grid:" + std::to_string(Grid::getGridNum());
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	last_text_textures->push_back(text);

	msg = u8"GameObjectNum: <Total:" + std::to_string(GameObject::getGameObjectNum())
		+ u8"> <Character:" + std::to_string(Chara::getCharaNum())
		+ u8"> <Facility:" + std::to_string(Facility::getFacilityNum())
		+ u8"> <Projectile:" + std::to_string(Projectile::getProjectileNum())
		+ u8">";
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	last_text_textures->push_back(text);

	msg = u8"PhysicsNum: <Object:" + std::to_string(PhysicsObject::getPhysicsObjectNum())
		+ u8"> <Character:" + std::to_string(PhysicsChara::getPhysicsCharaNum())
		+ u8"> <Facility:" + std::to_string(PhysicsFacility::getPhysicsFacillityNum())
		+ u8"> <Projectile:" + std::to_string(PhysicsProjectile::getPhysicsProjectilleNum())
		+ u8">";
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	last_text_textures->push_back(text);


	const int grid_x = static_cast<int>(floor(UISystem::getInstance()->mouseX_world));
	const int grid_y = static_cast<int>(floor(UISystem::getInstance()->mouseY_world));
	msg = u8"GridAt:(" + std::to_string(grid_x)
		+ u8"," + std::to_string(grid_y)
		+ u8") MousePosition:(" + std::to_string(UISystem::getInstance()->mouseX_window)
		+ u8"," + std::to_string(UISystem::getInstance()->mouseY_window)
		+ u8")";
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	last_text_textures->push_back(text);

	const auto g= WorldSystem::getInstance()->getGrid(grid_x, grid_y);

	if(g==nullptr)
	{
		msg = u8"Outside Grid";
		rect.y += rect.h;
		text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
		SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
		last_text_textures->push_back(text);
	}else
	{
		msg = u8"CharaNum:" + std::to_string(g->list_physics_chara->size())
			+ u8" FacilityNum:" + std::to_string(g->list_physics_facility->size())
			+ u8" ProjectileNum:" + std::to_string(g->list_physics_projectile->size());
		rect.y += rect.h;
		text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
		SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
		last_text_textures->push_back(text);
	}
	msg = u8"EnemyNum:" + std::to_string(Warrior::getWarriorNum())
		+ u8" MonsterNum:" + std::to_string(Monster::getMonsterNum());
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	last_text_textures->push_back(text);

	msg = u8"EnemyWaveNum:" + std::to_string(WorldSystem::getInstance()->enemy_wave_num)
		+ u8" EnemyWaveCD:" + std::to_string(WorldSystem::getInstance()->enemy_wave_CD)
		+ u8" GoldustEnergy:" + std::to_string(static_cast<int>(WorldSystem::getInstance()->goldust_energy));
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	last_text_textures->push_back(text);

	msg = u8"TimeSpeed:" + std::to_string(static_cast<int>(GlobalData::getTimeSpeed()))
		+ u8" TimePause:" + std::to_string(GlobalData::flag_stop);
	rect.y += rect.h;
	text = GameToolkit::getRenderedText(msg.c_str(), { 255,255,255,255 }, &rect.w, &rect.h);
	SDL_RenderCopy(GlobalData::sdl_renderer, text, nullptr, &rect);
	last_text_textures->push_back(text);
}
