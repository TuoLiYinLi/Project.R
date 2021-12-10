#include "Chara.h"
#include "SDL.h"


Chara* Chara::createNew() {
	Chara* c = new Chara();
	if (!c) {
		SDL_Log(u8"���� ����Chara�ڴ治��");
	}
	return c;
}

Chara::Chara()
{
	name = u8"default_chara";
	action = CharaAction::idle;

	animation_progress = 0;
}

Chara::~Chara()
{
	
}
