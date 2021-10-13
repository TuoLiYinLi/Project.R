#include "Chara.h"
#include "Defined.h"
#include "GameToolkit.h"

int Chara::currentCharaNum = 0;

void Chara::renewPosition()
{
	for (auto it = occupiedGrids->begin(); it != occupiedGrids->end(); it++)
	{
		Grid* grid = *it;
		grid->charaList->remove(this);
		//std::cout << "remove 1\n";
	}
	occupiedGrids->clear();
	MapSystem::getInstance()->occupyGrid(this);
}

int Chara::getCurrentCharaNum() {
	return currentCharaNum;
}

AnimType Chara::getAnimType()
{
#ifdef _DEBUG
	std::cout << "\t\tERROR:Chara::getAnimType()不可调用未定义的虚函数\n";
#endif // _DEBUG
	return AnimType::size;
}

void Chara::move(DirectionType d)
{
	//只要目标处没有完全阻挡,都是可以移动的
	std::cout << "角色开始移动\n";
	
	if (form.stamina < form.moveST)return;

	switch (d)
	{
	case DirectionType::right:
		if (gameToolkit::ifAbsoluteBlocked(x + 1, y))return;
		this->flip = false;
		movingX = 1;
		animProgress = 0;
		actionType = ActionType::move;
		break;
	case DirectionType::up:
		if (gameToolkit::ifAbsoluteBlocked(x, y - 1))return;

		if (!gameToolkit::ifWalkable(x, y - 1) &&
			( !gameToolkit::ifSwimable(x, y - 1) || movingType != MovingType::fly))return;
		movingY = -1;
		animProgress = 0;
		actionType = ActionType::move;
		break;
	case DirectionType::left:
		if (gameToolkit::ifAbsoluteBlocked(x - 1, y))return;
		this->flip = true;
		movingX = -1;
		animProgress = 0;
		actionType = ActionType::move;
		break;
	case DirectionType::down:
		if (gameToolkit::ifAbsoluteBlocked(x, y + 1))return;
		movingY = +1;
		animProgress = 0;
		actionType = ActionType::move;
		break;
	default:
		throw d;
		break;

	}
	form.stamina -= form.moveST;
	std::cout << "剩余ST"<<form.stamina<<"\n";
}

void Chara::useBasicSkill(bool _flip)
{
	
	if (form.stamina < form.basicSkillST)return;

	flip = _flip;
	
	animProgress = 0;
	actionType = ActionType::basicSkill;

	form.stamina -= form.basicSkillST;
	
}

void Chara::useSpecialSkill(bool _flip)
{
	
	if (form.stamina < form.specialSkillST)return;

	flip = _flip;

	animProgress = 0;
	actionType = ActionType::specialSkill;

	form.stamina -= form.specialSkillST;
	
}

void Chara::breed()
{
	
	if (form.breedTime == 0)return;
}

Chara* Chara::createNew() {
	Chara* c=new Chara();
	if (c == nullptr) {
#ifdef _DEBUG
		std::cout << "\t\tERROR:Chara::createNew()申请内存失败,值是nullptr\n";
#endif // _DEBUG
	}
	return c;
	
}


void Chara::destroy() {
	delete this;
}

Chara::Chara() {
#ifdef CHARA_DEBUG
	std::cout << "\tChara::Chara()\n";
#endif // CHARA_DEBUG
	CharaSystem::getInstance()->charaList->push_back(this);
	CharaSystem::getInstance()->reportMemory();
	
	currentCharaNum++;

	tag = Tag::Defaule;

	name = "new Chara";
	animUnit = nullptr;
	form = Form();

	ally = AllyType::ally;

	deathSpeed = 0;
	idleSpeed = 0;
	breathType = BreathType::both;
	movingType = MovingType::walk;
	actionType = ActionType::idle;
	animProgress = 0;

	//geneList = nullptr;
	x = 0;
	y = 0;
	movingX = 0;
	movingY = 0;
	bodyWidth = 0;
	bodyHeight = 0;
	deltaX = 0;
	deltaY = 0;
	flip = false;

	burnDamage = 0;
	poisionedDamage = 0;
	breath = 600;
	stifleDamage = 0;
	recoverAccumulate = 0;
	staminaAccumulate = 0;

	fallingY = 0;
	fallingDist = 0;

	occupiedGrids = new std::list<Grid*>();
	this->renewPosition();
}


Chara::~Chara() {
#ifdef CHARA_DEBUG
	std::cout << "\tChara::~Chara()\n";
#endif // CHARA_DEBUG
	currentCharaNum--;
	
	if (this->animUnit != nullptr) {
		AnimSystem::getInstance()->removeAnimUnit(this->animUnit);
		animUnit = nullptr;
	} 
	if (occupiedGrids != nullptr) {
		for (auto it = occupiedGrids->begin(); it != occupiedGrids->end(); it++)
		{
			Grid* grid = *it;
			grid->charaList->remove(this);
			//std::cout << "remove 1\n";
		}
		occupiedGrids->clear();
		delete occupiedGrids;
		occupiedGrids = nullptr;
	}

}

void Chara::onDeath()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onDeath()\n";
#endif // CHARA_ACTION_DEBUG
}

void Chara::onBasicSkill() {
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onBasicSkill()\n";
#endif // CHARA_ACTION_DEBUG
}

void Chara::onSpecialSkill() {
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onSpecialSkill()\n";
#endif // CHARA_ACTION_DEBUG
}

void Chara::onMove()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onMove()\n";
#endif // CHARA_ACTION_DEBUG
}

void Chara::onIdle()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onIdle()\n";
#endif // CHARA_ACTION_DEBUG
}

void Chara::onImpact()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onImpact()\n";
#endif // CHARA_ACTION_DEBUG
}

void Chara::onBurning()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onBurning()\n";
#endif // CHARA_ACTION_DEBUG
}

void Chara::onHit(Form* form)
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onHit()\n";
#endif // CHARA_ACTION_DEBUG
}

void Chara::onBreed()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onBreed()\n";
#endif // CHARA_ACTION_DEBUG
}

void Chara::onAnytime()
{
#ifdef CHARA_ACTION_DEBUG
	std::cout << "\t\tChara::onAnytime()\n";
#endif // CHARA_ACTION_DEBUG
}
