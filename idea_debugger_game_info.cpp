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
		rendering_unit->flag_enable = true;
	}else
	{
		rendering_unit->flag_enable = false;
	}
}

idea_debugger_game_info::idea_debugger_game_info()
{
	name = L"game_info_debugger";

	rendering_unit = RenderingUnit::createNew();
	rendering_unit->deltaX = 0;
	rendering_unit->deltaY = 0;
	rendering_unit->width = WINDOW_WIDTH;
	rendering_unit->height = WINDOW_HEIGHT;
	rendering_unit->reference = RenderingReference::window;
	rendering_unit->depth = DEPTH_EXTRA + 2;

	create_texture();
}

idea_debugger_game_info::~idea_debugger_game_info()
{
	destroy_texture();
}

void idea_debugger_game_info::renew_texture() const
{
	destroy_texture();
	create_texture();
}

void idea_debugger_game_info::create_texture() const
{
	int w, h;

	const auto t = GameToolkit::createUnicodeText(create_text().c_str(), { 255,255,255,255 }, WINDOW_WIDTH / 3, &w, &h);

	rendering_unit->setTexture(t);
	rendering_unit->width = static_cast<double>(w);
	rendering_unit->height = static_cast<double>(h);
}

void idea_debugger_game_info::destroy_texture() const
{
	//手动销毁材质
	if (rendering_unit->getTexture())
	{
		SDL_DestroyTexture(rendering_unit->getTexture());
		rendering_unit->setTexture(nullptr);
	}
}

std::wstring idea_debugger_game_info::create_text() const
{
	//performance
	std::wstring msg = L"[Performance]\nphysics frame:" + std::to_wstring(GlobalData::getTimePhysicsFrames())
		+ L"\nFPS:" + std::to_wstring(GlobalData::getFPS()) + L" delta:" + std::to_wstring(GlobalData::getTimeDelta());
	//statistics
	msg += L"\n[Statistics]\nRenderingUnit:" + std::to_wstring(RenderingUnit::getRenderingUnitNum())
		+ L" Grid:" + std::to_wstring(Grid::getGridNum())
		+ L"\nGameObjectNum:<Total:" + std::to_wstring(GameObject::getGameObjectNum())
		+ L"> <Character:" + std::to_wstring(Chara::getCharaNum())
		+ L"> <Facility:" + std::to_wstring(Facility::getFacilityNum())
		+ L"> <Projectile:" + std::to_wstring(Projectile::getProjectileNum())
		+ L">\nPhysicsNum:<Object:" + std::to_wstring(PhysicsObject::getPhysicsObjectNum())
		+ L"> <Character:" + std::to_wstring(PhysicsChara::getPhysicsCharaNum())
		+ L"> <Facility:" + std::to_wstring(PhysicsFacility::getPhysicsFacilityNum())
		+ L"> <Projectile:" + std::to_wstring(PhysicsProjectile::getPhysicsProjectileNum())
		+ L">";

	//grid info
	const int grid_x = static_cast<int>(floor(UISystem::getInstance()->mouseX_world));
	const int grid_y = static_cast<int>(floor(UISystem::getInstance()->mouseY_world));
	msg += L"\n[Cursor info]\nGrid at:(" + std::to_wstring(grid_x)+ L"," + std::to_wstring(grid_y)
		+ L") MousePosition:(" + std::to_wstring(UISystem::getInstance()->mouseX_window)
		+ L"," + std::to_wstring(UISystem::getInstance()->mouseY_window)+ L")";
	const auto g = WorldSystem::getInstance()->getGrid(grid_x, grid_y);
	if (g == nullptr)
	{
		msg += L"\nOutside Grid";
	}
	else
	{
		msg += L"\nCharaNum:" + std::to_wstring(g->list_physics_chara->size())
			+ L" FacilityNum:" + std::to_wstring(g->list_physics_facility->size())
			+ L" ProjectileNum:" + std::to_wstring(g->list_physics_projectile->size());
	}
	if(UISystem::getInstance()->last_tar)
	{
		msg += L"\nUI target:" + UISystem::getInstance()->last_tar->name;
	}else
	{
		msg += L"\nUI target:null";
	}

	//game info
	msg += L"\n[Game info]\nTimeSpeed:" + std::to_wstring(static_cast<int>(GlobalData::getTimeSpeed()))
		+ L" TimePause:" + std::to_wstring(GlobalData::flag_stop)
		+ L"\nWarriorNum:" + std::to_wstring(Warrior::getWarriorNum())
		+ L" MonsterNum:" + std::to_wstring(Monster::getMonsterNum())
		+ L" EnemyWaveNum:" + std::to_wstring(WorldSystem::getInstance()->enemy_wave_num)
		+ L" EnemyWaveCD:" + std::to_wstring(WorldSystem::getInstance()->enemy_wave_CD)
		+ L" GoldustEnergy:" + std::to_wstring(static_cast<int>(WorldSystem::getInstance()->goldust_energy));
	return msg;
}
