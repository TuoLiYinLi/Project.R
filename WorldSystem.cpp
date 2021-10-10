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
			std::cout << "\t\tERROR:new WorldSystem()�����ڴ�ʧ�ܣ�ֵΪnullptr\n";
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
		std::cout << "\t\tERROR:��ֹ�Ƴ�ֵΪnullptr��Chara*\n";
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
	//������ɫ�б�
	auto it = charaSys->charaList->begin();
	while (true)
	{
		//�˳�ѭ��
		if (it == charaSys->charaList->end()) {
			break;
		}
		//��ȡ��ɫ
		auto chara = *it;
		//ˢ�¼����ɫ��λ��
		{
			//��������λ��
			//��ɫ�ĺ����˶�
			if (chara->movingX > 0) {
				//chara->flip = false;
				//�����ƶ�
				double moveDist = double(1) / chara->form.moveTime;//����һ֡ʵ���ƶ��Ķ�С����
				chara->x += moveDist;
				chara->movingX -= moveDist;
				if (abs(chara->movingX) < moveDist) {
					chara->x += chara->movingX;
					chara->movingX = 0;
				}
				chara->renewPosition();//ˢ�½�ɫ��ռ��λ��
			}
			else if (chara->movingX < 0)
			{
				//chara->flip = true;
				//�����ƶ�
				double moveDist = double(1) / chara->form.moveTime;
				chara->x -= moveDist;
				chara->movingX += moveDist;
				if (abs(chara->movingX) < moveDist) {
					chara->x += chara->movingX;
					chara->movingX = 0;
				}
				chara->renewPosition();
			}
			//��ɫ�Ĵ�ֱ�����˶�
			if (chara->movingY > 0) {
				//�����ƶ�
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
				//�����ƶ�
				double moveDist = double(1) / chara->form.moveTime;
				chara->y -= moveDist;
				chara->movingY += moveDist;
				if (abs(chara->movingY) < moveDist) {
					chara->y += chara->movingY;
					chara->movingY = 0;
				}
				chara->renewPosition();
			}
			//��ɫ׹���λ�ø���
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
		//������ɫ׹��,�����ǽ�ɫ���ܷ�����ͣ����һ��׹������
		if (chara->actionType == ActionType::idle &&
			chara->movingType != MovingType::fly &&
			gameToolkit::ifFalling(round(chara->x), round(chara->y), chara->bodyWidth, chara->bodyHeight))
		{
			//std::cout << "��ɫ�����ñ�Ϊ׹��\n";
			chara->animProgress = 0;
			chara->actionType = ActionType::falling;
			chara->fallingY += 1;
			chara->fallingDist += 1;
		}
		//�ڽ�ɫ�������һ����λ���жϽ�ɫ�Ƿ�����׹��
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
		
		//�жϽ�ɫ�Ƿ��Ѿ�����,��������
		if (chara->actionType == ActionType::death) {
			if (chara->animProgress>=chara->deathSpeed) {
				//��������,�Ƴ���ɫ,����ѭ��
				chara->onDeath();
				it = charaSys->removeChara(it);
				std::cout << "\t\tһ����ɫ��������ֵ�����Ѿ��������Ƴ�\n";
				continue;
			}
		}
		//�жϽ�ɫ�Ƿ���Կ���
		else 
		{
			//ˢ�¼����ɫ����ֵ
			{
				//st�ָ�
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

				//�����ָ�
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
				//�ж�Ч��
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
				//ȼ��Ч��
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
				//��ûЧ��(δ���)
				{}

				//�����ж�
				if (chara->form.health <= 0 && chara->actionType != ActionType::death) {
					chara->animProgress = 0;
					chara->actionType = ActionType::death;
				}
			}
			//����״̬
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
			

			//���п���
			if (chara->movingX == 0 && chara->movingY == 0 && chara->form.beatback == 0 && chara->actionType == ActionType::idle) {

			}
		}
		//���¶���
		{
			//��ȡ����ʹ�õĶ�������
			AnimType animType = chara->getAnimType();
			chara->animUnit->type = animType;
			//��ȡ����ʹ�õĶ�����֡����
			int animLength = animSys->animList->at(int(animType))->size();
			//��ȡĿ�궯����ʱ�䳤��
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
				std::cout << "\t\tERROR:switch (chara->actionType)���ʹ���\n";
	#endif // _DEBUG
				break;
			}
			if (tarAnimTime > 0) {
				chara->animUnit->animProgress = floor(double(chara->animProgress) / tarAnimTime * animLength);
				if (chara->animUnit->animProgress >= animLength) {
					chara->animUnit->animProgress -= animLength - 1;
				}
			}
			//ͬ��λ��
			chara->animUnit->set(chara->x, chara->y);
			if (chara->flip) {
				chara->animUnit->flip = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				chara->animUnit->flip = SDL_FLIP_NONE;
			}
			
			//���ö���
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
		
		//ѭ������
		it++;
	}
}

void WorldSystem::faciLogicGo()
{
	auto it = faciSys->facilityList_dynamic->begin();
	//��̬��ʩ��������
	while (true)
	{
		//�˳�ѭ��
		if (it == faciSys->facilityList_dynamic->end()) {
			break;
		}
		//��ȡ��ʩ
		Facility* faci = *it;
		//������ʩλ��

		//�����ʩ����
		if (faci->stateType == StateType::death) {
			//�ж���ʩ����
			if (faci->animProgress >= faci->deathLength) {
				faci->onDeath();
				it = faciSys->removeFacility_dynamic(it);
				continue;
			}
		}
		else
		{
			//������ʩ��ֵ

			faci->onAnytime();
			//�������,ֻ����activateCycle>0ʱ����Ч
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
			//�������
			if (faci->health <= 0) {
				faci->animProgress = 0;
				faci->stateType = StateType::death;
			}

		}
		//���¶���
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
		//ͬ��λ��
		faci->animUnit->set(faci->x, faci->y);

		//���ö���
		faci->animProgress++;
		if (faci->animProgress >= tarAnimTime && faci->stateType != StateType::death) {
			faci->animProgress = 0;
			faci->stateType = StateType::idle;
		}
		//ѭ������
		it++;
	}
}

void WorldSystem::projLogicGo()
{
	//Ͷ����ѭ��
	auto i = projSys->projList->begin();
	while (true)
	{
		//�˳�ѭ��
		if (i == projSys->projList->end()) {
			break;
		}
		Projectile* pjt = *i;
		//Ͷ������ʧ
		if (pjt->livingTime <= 0) {
			pjt->onEnd();
			i=projSys->projList->erase(i);
			pjt->destroy();
		}
		else
		{
			pjt->livingTime--;
			//����λ��
			pjt->x += pjt->vx;
			pjt->vx += pjt->ax;
		
			pjt->y += pjt->vy;
			pjt->vy += pjt->ay;

			pjt->onFlying();
			//ͬ���Ͷ���
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
	//(1/2)�������ӱ���
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
	//(2/2)������������
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




