#include "Form.h"

Form::Form() {
	{
		healthMax = 0;
		health = 0;
		recovery = 0;
		corruption = 0;
		stamina = 0;
		staminaMax = 0;
		staminaRecover = 0;

		moveTime = 0;
		moveST = 0;
		basicSkillTime = 0;
		basicSkillST = 0;
		specialSkillTime = 0;
		specialSkillST = 0;
		breedSpeed = 0;

		breedTime = 0;
		speedupTime = 0;
		speedupEffect = 0;
		beatback = 0;
		sealedTime = 0;
		vigorEffect = 0;
		vigorTime = 0;
		darkTime = 0;
		burnEffect = 0;
		burnTime = 0;
		poisionedEffect = 0;
		poisionedTime = 0;
		defenceTime = 0;
		stunnedTime = 0;
	}
}

Form::~Form() {

}
void Form::setBasicPart(
	int _healthMax,
	int _health,
	double _recovery,
	int _staminaMax,
	int _stamina,
	double _staminaRecover,
	int _corruption) {
	healthMax = _healthMax;
	health = _health;
	recovery = _recovery;
	corruption = _corruption;
	stamina = _stamina;
	staminaMax = _staminaMax;
	staminaRecover = _staminaRecover;
}
void Form::setActionPart(
	int _moveTime ,
	int _moveST ,
	int _basicSkillTime ,
	int _basicSkillST ,
	int _specialSkillTime ,
	int _specialSkillST ,
	int _breedSpeed ) {
	moveTime = _moveTime;
	moveST = _moveST;
	basicSkillTime = _basicSkillTime;
	basicSkillST = _basicSkillST;
	specialSkillTime = _specialSkillTime;
	specialSkillST = _specialSkillST;
	breedSpeed = _breedSpeed;
}
void Form::setEffectPart(
	double _speedupEffect,
	double _vigorEffect ,
	double _beatback ,
	double _poisionedEffect ,
	double _burnEffect ,
	int _breedTime ,
	int _speedupTime ,
	int _sealedTime ,
	int _vigorTime ,
	int _defenceTime ,
	int _burnTime ,
	int _stunnedTime ,
	int _darkTime ,
	int _poisionedTime 
	) {
	breedTime = _breedTime;
	speedupTime = _speedupTime;
	speedupEffect = _speedupEffect;
	beatback = _beatback;
	sealedTime = _sealedTime;
	vigorEffect = _vigorEffect;
	vigorTime = _vigorTime;
	darkTime = _darkTime;
	burnEffect = _burnEffect;
	burnTime = _burnTime;
	poisionedEffect = _poisionedEffect;
	poisionedTime = _poisionedTime;
	defenceTime = _defenceTime;
	stunnedTime = _stunnedTime;
}