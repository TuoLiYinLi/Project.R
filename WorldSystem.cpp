#include "WorldSystem.h"
#include "Defined.h"
#include "GameToolkit.h"
WorldSystem* WorldSystem::instance = nullptr;

WorldSystem* WorldSystem::getInstance()
{
	if (instance == nullptr) {
		instance = new WorldSystem();
		if (instance == nullptr) {
#ifdef _DEBUG
			std::cout << "\t\tERROR:new WorldSystem()申请内存失败，值为nullptr\n";
#endif //_DEBUG
		}
	}
	return instance;
}

void WorldSystem::destroyInstance()
{
	delete this;
}

void WorldSystem::removeChara(Chara* chara)
{
#ifdef WORLD_SYSTEM_DEBUG
	std::cout << "WorldSystem::removeChara(Chara* chara)\n";
	if (chara == nullptr) {
		std::cout << "\t\tERROR:禁止移除值为nullptr的Chara*\n";
		return;
	}
#endif // WORLD_SYSTEM_DEBUG
	charaSys->removeChara(chara);
}

Facility* WorldSystem::addFacility_static(Facility* facility)
{
	faciSys->facilityList_static->push_back(facility);
	return facility;
}

void WorldSystem::removeFacility_static(Facility* facility)
{
	faciSys->facilityList_static->remove(facility);
}

void WorldSystem::logicGo()
{
	projLogicGo();
	faciLogicGo();
	charaLogicGo();
	particleLogicGo();
}

void WorldSystem::charaLogicGo()
{
	//遍历角色列表
	auto it = charaSys->charaList->begin();
	while (true)
	{
		//退出循环
		if (it == charaSys->charaList->end()) {
			break;
		}
		//获取角色
		auto chara = *it;
		//刷新计算角色的位置
		{
			//人物行走位移
			//角色的横向运动
			if (chara->movingX > 0) {
				//chara->flip = false;
				//向右移动
				double moveDist = double(1) / chara->form.moveTime;//在这一帧实际移动的短小距离
				chara->x += moveDist;
				chara->movingX -= moveDist;
				if (abs(chara->movingX) < moveDist) {
					chara->x += chara->movingX;
					chara->movingX = 0;
				}
				chara->renewPosition();//刷新角色的占用位置
			}
			else if (chara->movingX < 0)
			{
				//chara->flip = true;
				//向左移动
				double moveDist = double(1) / chara->form.moveTime;
				chara->x -= moveDist;
				chara->movingX += moveDist;
				if (abs(chara->movingX) < moveDist) {
					chara->x += chara->movingX;
					chara->movingX = 0;
				}
				chara->renewPosition();
			}
			//角色的垂直方向运动
			if (chara->movingY > 0) {
				//向下移动
				double moveDist = double(1) / chara->form.moveTime;
				chara->y += moveDist;
				chara->movingY -= moveDist;
				if (abs(chara->movingY) < moveDist) {
					chara->y += chara->movingY;
					chara->movingY = 0;
				}
				chara->renewPosition();
			}
			else if (chara->movingY < 0)
			{
				//向上移动
				double moveDist = double(1) / chara->form.moveTime;
				chara->y -= moveDist;
				chara->movingY += moveDist;
				if (abs(chara->movingY) < moveDist) {
					chara->y += chara->movingY;
					chara->movingY = 0;
				}
				chara->renewPosition();
			}
			//角色坠落的位置更新
			if (chara->fallingY > 0) {
				double moveDist = FALLING_SPEED;
				chara->y += moveDist;
				chara->fallingY -= moveDist;
				if (chara->fallingY < moveDist) {
					chara->y += chara->fallingY;
					chara->fallingY = 0;
				}
				chara->renewPosition();
			}
		}
		//发动角色坠落,条件是角色不能飞行且停滞于一个坠落区域
		if (chara->actionType == ActionType::idle &&
			chara->movingType != MovingType::fly &&
			gameToolkit::ifFalling(round(chara->x), round(chara->y), chara->bodyWidth, chara->bodyHeight))
		{
			//std::cout << "角色从闲置变为坠落\n";
			chara->animProgress = 0;
			chara->actionType = ActionType::falling;
			chara->fallingY += 1;
			chara->fallingDist += 1;
		}
		//在角色掉落完成一个各位后判断角色是否会继续坠落
		if (chara->actionType == ActionType::falling &&
			chara->fallingY == 0) {
			if (gameToolkit::ifFalling(round(chara->x), round(chara->y), chara->bodyWidth, chara->bodyHeight)) {
				chara->fallingY += 1;
				chara->fallingDist += 1;
			}
			else
			{
				chara->actionType = ActionType::idle;
				chara->onImpact();
				chara->fallingY = 0;
			}
		}
		
		//判断角色是否已经死亡,触发死亡
		if (chara->actionType == ActionType::death) {
			if (chara->animProgress>=chara->deathSpeed) {
				//触发死亡,移除角色,结束循环
				chara->onDeath();
				it = charaSys->removeChara(it);
				std::cout << "\t\t一个角色由于生命值归零已经死亡并移除\n";
				continue;
			}
		}
		//判断角色是否可以控制
		else 
		{
			//刷新计算角色的数值
			{
				//st恢复
				chara->staminaAccumulate += chara->form.staminaRecover;
				if (chara->staminaAccumulate >= 1)
				{
					auto stamina_delta = floor(chara->staminaAccumulate);
					chara->form.stamina += stamina_delta;
					chara->staminaAccumulate -= stamina_delta;
				}
				if (chara->form.stamina > chara->form.staminaMax) {
					chara->form.stamina = chara->form.staminaMax;
				}

				//生命恢复
				chara->recoverAccumulate += chara->form.recovery;
				if (chara->recoverAccumulate >= 1)
				{
					auto recover_delta = floor(chara->recoverAccumulate);
					chara->form.health += recover_delta;
					chara->recoverAccumulate -= recover_delta;
				}
				if (chara->form.health > chara->form.healthMax) {
					chara->form.health = chara->form.healthMax;
				}
				//中毒效果
				if (chara->form.poisionedTime > 0) {
					chara->form.poisionedTime--;
					chara->poisionedDamage += chara->form.poisionedEffect * chara->form.healthMax;
					if (chara->poisionedDamage >= 1) {
						auto poisioned_delta = floor(chara->poisionedDamage);
						chara->form.health -= poisioned_delta;
						chara->poisionedDamage -= poisioned_delta;
					}
					if (chara->form.health < 0) {
						chara->form.health = 0;
					}
				}
				//燃烧效果
				if (chara->form.burnTime > 0) {
					chara->form.burnTime--;
					chara->burnDamage += chara->form.burnEffect;
					if (chara->burnDamage >= 1) {
						auto burn_delta = floor(chara->burnDamage);
						chara->form.health -= burn_delta;
						chara->burnDamage -= burn_delta;
					}
					if (chara->form.health < 0) {
						chara->form.health = 0;
					}
				}
				//淹没效果(未完成)
				{}

				//死亡判断
				if (chara->form.health <= 0 && chara->actionType != ActionType::death) {
					chara->animProgress = 0;
					chara->actionType = ActionType::death;
				}
			}
			//触发状态
			chara->onAnytime();
			if (chara->actionType != ActionType::death)
			{
				if (chara->actionType == ActionType::idle&& chara->movingX == 0 && chara->movingY == 0 && chara->form.beatback == 0 && chara->fallingY == 0) {
					chara->onIdle();
				}
				if (chara->movingX != 0 || chara->movingY != 0 || chara->form.beatback != 0||chara->fallingY!=0) {
					chara->onMove();
				}
				if (chara->form.burnTime > 0) {
					chara->onBurning();
				}
			}
			

			//进行控制
			if (chara->movingX == 0 && chara->movingY == 0 && chara->form.beatback == 0 && chara->actionType == ActionType::idle) {

			}
		}
		//更新动画
		{
			//获取正在使用的动画种类
			AnimType animType = chara->getAnimType();
			chara->animUnit->type = animType;
			//获取正在使用的动画的帧总数
			int animLength = animSys->animList->at(int(animType))->size();
			//获取目标动画的时间长度
			int tarAnimTime = 0;
			switch (chara->actionType)
			{
			case ActionType::idle:
				tarAnimTime = chara->idleSpeed;
				break;
			case ActionType::move:
				tarAnimTime = chara->form.moveTime;
				break;
			case ActionType::swim:
				tarAnimTime = chara->form.moveTime;
				break;
			case ActionType::basicSkill:
				tarAnimTime = chara->form.basicSkillTime;
				break;
			case ActionType::specialSkill:
				tarAnimTime = chara->form.specialSkillTime;
				break;
			case ActionType::breed:
				tarAnimTime = chara->form.breedSpeed;
				break;
			case ActionType::death:
				tarAnimTime = chara->deathSpeed;
				break;
			case ActionType::falling:
				tarAnimTime = chara->idleSpeed;
				break;
			default:
	#ifdef _DEBUG
				std::cout << "\t\tERROR:switch (chara->actionType)类型错误\n";
	#endif // _DEBUG
				break;
			}
			if (tarAnimTime > 0) {
				chara->animUnit->animProgress = floor(double(chara->animProgress) / tarAnimTime * animLength);
				if (chara->animUnit->animProgress >= animLength) {
					chara->animUnit->animProgress -= animLength - 1;
				}
			}
			//同步位置
			chara->animUnit->set(chara->x, chara->y);
			if (chara->flip) {
				chara->animUnit->flip = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				chara->animUnit->flip = SDL_FLIP_NONE;
			}
			
			//重置动画
			chara->animProgress++;
			if (chara->animProgress >= tarAnimTime && chara->actionType != ActionType::death ) {
				if (chara->actionType == ActionType::breed) 
				{
					chara->onBreed();
				}
				else if(chara->actionType == ActionType::specialSkill) 
				{
					chara->onSpecialSkill();
				}
				else if (chara->actionType == ActionType::basicSkill)
				{
					chara->onBasicSkill();
				}
				if (chara->actionType != ActionType::falling) {
					chara->actionType = ActionType::idle;
				}
				chara->animProgress = 0;
			}
		}
		
		//循环继续
		it++;
	}
}

void WorldSystem::faciLogicGo()
{
	auto it = faciSys->facilityList_dynamic->begin();
	//动态设施遍历更新
	while (true)
	{
		//退出循环
		if (it == faciSys->facilityList_dynamic->end()) {
			break;
		}
		//获取设施
		Facility* faci = *it;
		//更新设施位置

		//检查设施死亡
		if (faci->stateType == StateType::death) {
			//判断设施销毁
			if (faci->animProgress >= faci->deathLength) {
				faci->onDeath();
				it = faciSys->removeFacility_dynamic(it);
				continue;
			}
		}
		else
		{
			//更新设施数值

			faci->onAnytime();
			//激活更新,只有在activateCycle>0时才有效
			if (faci->activateCycle > 0) {
				faci->activateCD++;
				if (faci->activateCD >= faci->activateCycle) {
					faci->activateCD = 0;
					faci->stateType = StateType::activated;
				}
			}

			if (faci->stateType == StateType::activated) {
				faci->onActivate();
			}
			else if(faci->stateType == StateType::idle)
			{
				faci->onIdle();
			}
			//检查死亡
			if (faci->health <= 0) {
				faci->animProgress = 0;
				faci->stateType = StateType::death;
			}

		}
		//更新动画
		StateType stateType = faci->stateType;
		int animLength = animSys->animList->at(int(faci->getAnimType()))->size();
		int tarAnimTime = 0;
		switch (stateType)
		{
		case StateType::activated:
			tarAnimTime = faci->activateLength;
			break;
		case StateType::idle:
			tarAnimTime = faci->idleLength;
			break;
		case StateType::death:
			tarAnimTime = faci->deathLength;
			break;
		default:
			break;
		}
		if (tarAnimTime > 0) {
			faci->animUnit->animProgress = floor(double(faci->animProgress) / tarAnimTime * animLength);
			if (faci->animUnit->animProgress >= animLength) {
				faci->animUnit->animProgress -= animLength - 1;
			}
		}
		//同步位置
		faci->animUnit->set(faci->x, faci->y);

		//重置动画
		faci->animProgress++;
		if (faci->animProgress >= tarAnimTime && faci->stateType != StateType::death) {
			faci->animProgress = 0;
			faci->stateType = StateType::idle;
		}
		//循环继续
		it++;
	}
}

void WorldSystem::projLogicGo()
{
	//投射物循环
	auto i = projSys->projList->begin();
	while (true)
	{
		//退出循环
		if (i == projSys->projList->end()) {
			break;
		}
		Projectile* pjt = *i;
		//投射物消失
		if (pjt->livingTime <= 0) {
			pjt->onEnd();
			i=projSys->projList->erase(i);
			pjt->destroy();
		}
		else
		{
			pjt->livingTime--;
			//更新位置
			pjt->x += pjt->vx;
			pjt->vx += pjt->ax;
		
			pjt->y += pjt->vy;
			pjt->vy += pjt->ay;

			pjt->onFlying();
			//同步和动画
			pjt->animUnit->x = pjt->x;
			pjt->animUnit->y = pjt->y;

			int animLength = animSys->getInstance()->animList->at(int(pjt->animUnit->type))->size();
			pjt->animUnit->animProgress = floor(double(pjt->animProgress) / pjt->animCycle * animLength);
			if (pjt->animUnit->animProgress >=animLength) {
				pjt->animUnit->animProgress = animLength - 1;
			}
			pjt->animProgress++;
			if (pjt->animProgress >= pjt->animCycle) {
				pjt->animProgress = 0;
			}
			i++;
		}
	}
}

void WorldSystem::particleLogicGo()
{
	//(1/2)文字粒子遍历
	auto it = particleSys->ttfParticleList->begin();
	while (true)
	{
		if (it == particleSys->ttfParticleList->end()) {
			break;
		}
		auto p = *it;

		p->x += p->v_x;
		p->y += p->v_y;
		p->scale += p->v_scale;

		p->v_x += p->a_x;
		p->v_y += p->a_y;
		p->v_scale += p->a_scale;

		p->fontUnit->world_x = p->x;
		p->fontUnit->world_y = p->y;
		p->fontUnit->scale = p->scale;

		if ((*it)->livingTime <= 0) {
			animSys->removeTTFUnit((*it)->fontUnit);
			(*it)->destroy();
			it=particleSys->ttfParticleList->erase(it);
		}
		else {
			(*it)->livingTime--;
			it++;
		}
	}
	//(2/2)动画粒子历遍
	auto ir = particleSys->animParticleList->begin();
	while (true)
	{
		if (ir==particleSys->animParticleList->end()) {
			break;
		}
		if ((*ir)->livingTime<=0) {
			animSys->removeAnimUnit((*ir)->animUnit);
			(*ir)->destroy();
			ir = particleSys->animParticleList->erase(ir);
		}
		else
		{
			(*ir)->livingTime--;
			auto p = *ir;
			p->x += p->v_x;
			p->y += p->v_y;
			p->angle += p->v_angle;
			p->scale += p->v_scale;

			p->v_x += p->a_x;
			p->v_y += p->a_y;
			p->v_scale += p->a_scale;
			p->v_angle += p->a_angle;

			p->animUnit->angle = p->angle;
			p->animUnit->x = p->x;
			p->animUnit->y = p->y;
			p->animUnit->width = p->w * p->scale;
			p->animUnit->height = p->h * p->scale;
			int animLength = animSys->animList->at(int(p->animUnit->type))->size();
			p->animUnit->animProgress= round(double(p->animProgress) / p->animCycle * animLength) - 1;
			if (p->animUnit->animProgress < 0) {
				p->animUnit->animProgress = 0;
			}
			p->animProgress++;
			if (p->animProgress>=p->animCycle) {
				p->animProgress = 0;
			}
			ir++;
		}
	}
}

WorldSystem::WorldSystem()
{
	animSys = AnimSystem::getInstance();
	mapSys = MapSystem::getInstance();
	geneSys = GeneSystem::getInstance();
	projSys = ProjectileSystem::getInstance();
	charaSys = CharaSystem::getInstance();
	faciSys = FacilitySystem::getInstance();
	particleSys = ParticleSystem::getInstance();
}

WorldSystem::~WorldSystem()
{
	particleSys->destroyInstance();
	particleSys = nullptr;
	faciSys->destroyInstance();
	faciSys = nullptr;
	charaSys->destroyInstance();
	charaSys = nullptr;
	projSys->destroyInstance();
	projSys = nullptr;
	geneSys->destroyInstance();
	geneSys = nullptr;
	mapSys->destroyInstance();
	mapSys = nullptr;
	animSys->destroyInstance();
	animSys=nullptr;
}




