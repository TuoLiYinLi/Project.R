#include "Projectile.h"


Projectile* Projectile::createNew()
{
Projectile* p = new Projectile();
if (p == nullptr) {
#ifdef PROJECTILE_DEBUG
	std::cout << "\t\tERROR::new Projectile()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr\n";
#endif // PROJECTILE_DEBUG

}
return p;
}


Projectile::Projectile()
{
	animation_length = 60;
	animation_progress = 0;
	life_time = 60;
}

Projectile::~Projectile()
{

}