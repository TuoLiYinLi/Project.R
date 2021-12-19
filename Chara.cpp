#include "Chara.h"

#include "PhysicsFacility.h"
#include "SDL.h"


Chara* Chara::createNew() {
	Chara* c = new Chara();
	if (!c) {
		SDL_Log(u8"���� ����Chara�ڴ治��");
	}
	return c;
}

void Chara::update()
{
	
}


Chara::Chara()
{
	name = u8"default_chara";
	action = CharaAction::idle;

	animation_progress = 0;

	//��������ʩ
	physics_object = PhysicsFacility::createNew();
	physics_object->game_object = this;

	physics_object->bodyX = 1;
	physics_object->bodyY = 1;
}

Chara::~Chara()
{
	
}
