#include "ProjectileSystem.h"
#include "Defined.h"
ProjectileSystem* ProjectileSystem::instance = nullptr;

ProjectileSystem* ProjectileSystem::getInstance() {
#ifdef PROJECTILE_SYSTEM_DEBUG
	std::cout << "ProjectileSystem::getInstance()\n";
#endif // PROJECTILE_SYSTEM_DEBUG

	if (instance == nullptr) {
		instance = new ProjectileSystem();
	}
	return instance;
}

void ProjectileSystem::destroyInstance() {
#ifdef PROJECTILE_SYSTEM_DEBUG
	std::cout << "ProjectileSystem::destroyInstance()\n";
#endif // PROJECTILE_SYSTEM_DEBUG
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void ProjectileSystem::reportMemory() {
#ifdef PROJECTILE_SYSTEM_DEBUG
	std::cout << "ProjectileSystem::reportMemory()\n";
	std::cout << "\t\t������"<< Projectile::getCurrentProjNum() <<"��Projectileռ���ڴ�\n";
#endif // PROJECTILE_SYSTEM_DEBUG
}

ProjectileSystem::ProjectileSystem() {
#ifdef PROJECTILE_SYSTEM_DEBUG
	std::cout << "ProjectileSystem::ProjectileSystem()\n";
#endif // PROJECTILE_SYSTEM_DEBUG
	projList = new std::list<Projectile*>();
	if (projList == nullptr) {
#ifdef PROJECTILE_SYSTEM_DEBUG
		std::cout << "\t\tERROR:new std::list<Projectile*>()�����ڴ�ʧ�ܣ�ֵΪnullptr\n";
#endif // PROJECTILE_SYSTEM_DEBUG
	}
}

ProjectileSystem::~ProjectileSystem() {
#ifdef PROJECTILE_SYSTEM_DEBUG
	std::cout << "ProjectileSystem::~ProjectileSystem()\n";
#endif // PROJECTILE_SYSTEM_DEBUG
	reportMemory();
	int count = 0;
	if (projList != nullptr) {
		for (auto it = projList->begin(); it != projList->end(); it++)
		{
			if ((*it) != nullptr) {
				(*it)->destroy();
				(*it) = nullptr;
				count++;
			}
		}
#ifdef PROJECTILE_SYSTEM_DEBUG
		std::cout << "\t\t������projList��"<< count <<"��projectile\n";
#endif // PROJECTILE_SYSTEM_DEBUG
		delete projList;
		projList = nullptr;
	}

}
/*
void ProjectileSystem::addProjectile(Projectile* projectile)
{
#ifdef PROJECTILE_SYSTEM_DEBUG
	std::cout << "ProjectileSystem::addProjectile(Projectile* projectile)\n";
#endif // PROJECTILE_SYSTEM_DEBUG
	projList->push_back(projectile);
}
*/

void ProjectileSystem::removeProjectile(Projectile* projectile)
{
#ifdef PROJECTILE_SYSTEM_DEBUG
	std::cout << "ProjectileSystem::removeProjectile(Projectile* projectile)\n";
#endif // PROJECTILE_SYSTEM_DEBUG
	this->projList->remove(projectile);
	projectile->destroy();
	reportMemory();
}

