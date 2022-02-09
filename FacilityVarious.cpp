#include "FacilityVarious.h"
FacilityVarious* FacilityVarious::createNew()
{
	return new FacilityVarious();
}

FacilityVarious::FacilityVarious()
{
	flag_static = true;
	list_various_texture = new std::vector<AnimationType>();
}

FacilityVarious::~FacilityVarious()
{
	delete list_various_texture;
}

void FacilityVarious::setVariousTexture()
{
	if(!list_various_texture->empty())
	{
		const auto r= rand() % list_various_texture->size();
		animation_type_idle = list_various_texture->at(r);
	}
}
