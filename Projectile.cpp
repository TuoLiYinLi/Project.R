#include "Projectile.h"
#include "Defined.h"
#include "GameToolkit.h"

int Projectile::currentProjNum = 0;
/*
void Projectile::onHitCharaNearest(Chara* charalist)
{
	std::cout << "\t\tonHitCharaNearest\n";
}

void Projectile::onHitFacilityNearest(Facility* facilityList)
{
	std::cout << "\t\tonHitFacilityNearest\n";
}
*/

void Projectile::onEnd()
{
	std::cout << "\t\tonEnd\n";
}

void Projectile::onFlying()
{
	std::cout << "\t\tonFlying\n";
}

Projectile* Projectile::createNew()
{
	Projectile* p = new Projectile();
	if (p==nullptr) {
#ifdef PROJECTILE_DEBUG
		std::cout << "\t\tERROR::new Projectile()申请内存失败，值为nullptr\n";
#endif // PROJECTILE_DEBUG

	}
	return p;
}

void Projectile::destroy()
{
	delete this;
}

Projectile::Projectile()
{
#ifdef PROJECTILE_DEBUG
	std::cout << "\tProjectile::Projectile()\n";
#endif // PROJECTILE_DEBUG

	currentProjNum++;

	ProjectileSystem::getInstance()->projList->push_back(this);

	//type = ProjectileType::simple;
	allyType = AllyType::neutral;
	animUnit = nullptr;

	form = Form();
	/*
	geneList = new std::list<Gene*>();
	if (geneList==nullptr) {
#ifdef PROJECTILE_DEBUG
		std::cout << "\t\tERROR::new std::list<Gene*>()申请内存失败,值为nullptr\n";
#endif // PROJECTILE_DEBUG
	}
	*/
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	ax = 0;
	ay = 0;
	bodyWidth = 0;
	bodyHeight = 0;
	//radius = 0;
	animCycle = 0;
	animProgress = 0;
	livingTime = 0;
}

Projectile::~Projectile()
{
#ifdef PROJECTILE_DEBUG
	std::cout << "\tProjectile::~Projectile()\n";
#endif // PROJECTILE_DEBUG
	currentProjNum--;
	/*
	if (geneList != nullptr) {
		for (auto it = geneList->begin(); it != geneList->end(); it++)
		{
			if ((*it) != nullptr) {
				(*it)->destroy();
				(*it) = nullptr;
			}
		}
		delete geneList;
		geneList = nullptr;
	}
	*/
	if (animUnit != nullptr) {
		AnimSystem::getInstance()->removeAnimUnit(animUnit);
		animUnit = nullptr;
	}
}


int Projectile::getCurrentProjNum() {
	return currentProjNum;
}