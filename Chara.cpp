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
	//std::cout << "角色开始移动\n";
	
	if (form.stamina < form.moveST)return;

	switch (d)
	{
	case DirectionType::right:
		//std::cout << "角色向右移动\n";
		for (auto i = getHeadSpot(); i <= getStandSpot(); i++)
		{
			if (gameToolkit::ifAbsoluteBlocked(getRightSpot() + 1, i))return;
		}
		this->flip = false;
		movingX = 1;
		animProgress = 0;
		actionType = ActionType::move;
		break;
	case DirectionType::up:
		//std::cout << "角色向上移动\n";
		//仅上方有支撑的情况可以向上运动;
		for (auto i = getLeftSpot(); i <= getRightSpot(); i++)
		{
			//如果上方有阻挡当然不能向上
			if (gameToolkit::ifAbsoluteBlocked(i, getHeadSpot() - 1))return;
			//如果往上走需要检测那一格状态或者自己能否飞行
			if (!gameToolkit::ifWalkable(i, getStandSpot() - 1) &&
				( !gameToolkit::ifSwimable(i, getStandSpot() - 1) ||!ifFly))return;
		}
		movingY = -1;
		animProgress = 0;
		actionType = ActionType::move;
		break;
	case DirectionType::left:
		//std::cout << "角色向左移动\n";
		for (auto i = getHeadSpot(); i <= getStandSpot(); i++)
		{
			if (gameToolkit::ifAbsoluteBlocked(getLeftSpot() - 1, i))return;
		}
		this->flip = true;
		movingX = -1;
		animProgress = 0;
		actionType = ActionType::move;
		break;
	case DirectionType::down:
		std::cout << "角色向下移动\n";
		for (auto i = getLeftSpot(); i <= getRightSpot(); i++)
		{
			//如果下方有阻挡当然不能向上
			if (gameToolkit::ifAbsoluteBlocked(i, getStandSpot() + 1))return;
		}
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

double Chara::getHeadSpot()
{
	return y;
}

double Chara::getStandSpot()
{
	return y + bodyHeight - 1;
}

double Chara::getLeftSpot()
{
	return x;
}

double Chara::getRightSpot()
{
	return x + bodyWidth - 1;
}

Chara::Chara() {
#ifdef CHARA_DEBUG
	std::cout << "\tChara::Chara()\n";
#endif // CHARA_DEBUG
	CharaSystem::getInstance()->charaList->push_back(this);
	CharaSystem::getInstance()->reportMemory();
	
	currentCharaNum++;

	tag = Tag::default_tag;

	name = "new Chara";
	animUnit = nullptr;
	form = Form();

	ally = AllyType::ally;

	deathSpeed = 0;
	idleSpeed = 0;
	
	
	actionType = ActionType::idle;
	animProgress = 0;

	ifFly = false;
	ifSwim = true;
	ifBreathInWater = false;

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

	if (patrolArea==nullptr)
	{
		patrolArea = new std::vector<Grid*>();
	}
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

	if (patrolArea != nullptr)
	{
		delete patrolArea;
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
