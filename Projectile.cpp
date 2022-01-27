#include "Projectile.h"


Projectile* Projectile::createNew()
{
Projectile* p = new Projectile();
if (p == nullptr) {
#ifdef PROJECTILE_DEBUG
	std::cout << " ERROR::new Projectile()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr\n";
#endif // PROJECTILE_DEBUG

}
return p;
}

int Projectile::projectile_num = 0;

int Projectile::getProjectileNum()
{
	return projectile_num;
}

Projectile::Projectile()
{
	projectile_num ++;
	animation_length = 60;
	animation_progress = 0;
	life_time = 60;
}

Projectile::~Projectile()
{
	projectile_num--;
}