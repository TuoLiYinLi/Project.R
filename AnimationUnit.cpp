#include "AnimationUnit.h"
#include "Defined.h"

AnimationUnit* AnimationUnit::set(double _x, double _y, double _width, double _height, double _angle)
{
	this->x = _x;
	this->y = _y;
	if (_width > 0) {
		this->width = _width;
	}
	if (_height > 0) {
		this->height = _height;
	}
	this->angle = _angle;
	return this;
}

AnimationUnit* AnimationUnit::createNew() {
#ifdef ANIM_UNIT_DEBUG
	std::cout << "AnimationUnit::createNew()\n";
#endif // ANIM_UNIT_DEBUG

	AnimationUnit* au = new AnimationUnit();
	if (au == nullptr) {
#ifdef _DEBUG
		std::cout << "ERROR:new AnimationUnit()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr\n";
#endif // _DEBUG

	}
	return au;
}

void AnimationUnit::destroy() {
	delete this;
}

AnimationUnit::AnimationUnit() {
#ifdef ANIM_UNIT_DEBUG
	std::cout << "AnimationUnit::AnimationUnit()\n";
#endif // ANIM_UNIT_DEBUG

	AnimationSystem::getInstance()->animUnitList->push_back(this);

	currentNum++;

	depth = 0;
	type = AnimType::Default;
	animProgress = 0;

	deltaX = 0;
	deltaY = 0;

	x = 1;
	y = 1;

	width = 32;
	height = 32;

	angle = 0;
	flip = SDL_FLIP_NONE;
}

AnimationUnit::~AnimationUnit() {
#ifdef ANIM_UNIT_DEBUG
	std::cout << "AnimationUnit::~AnimationUnit()\n";
#endif // ANIM_UNIT_DEBUG
	currentNum--;
}

int AnimationUnit::currentNum = 0;


int AnimationUnit::getCurrentNum() {
	return currentNum;
}
