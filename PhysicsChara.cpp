#include "PhysicsChara.h"
#include "WorldSystem.h"
#include "SDL.h"
#include "Defined.h"

PhysicsChara* PhysicsChara::createNew()
{
	return new PhysicsChara();
}

PhysicsChara::PhysicsChara()
{
	physicsCharaNum++;

	//��ʼ������
	type_physics = PhysicsType::chara;

	can_fly = false;
	can_swim = false;

	impact = 0;

	moving = false;
	hitback = false;

	steady = false;

	moving_speed = 0;
	moving_direction = PhysicsDirection::right;
	moving_inertia = 0;

	falling_count = 0;

	//���Լ���ӵ���ɫ�����б�
	WorldSystem::getInstance()->list_physics_chara->push_front(this);
	//��ʼ��ǩ�������б�
	list_grid_signed = new std::list<Grid*>();


}

PhysicsChara::~PhysicsChara()
{
	//����ǩ���
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		const Grid* grid = *it;
		grid->list_physics_chara->remove(this);
	}
	list_grid_signed->clear();

	//���Լ��ӽ�ɫ�����б��Ƴ�
	WorldSystem::getInstance()->list_physics_chara->remove(this);
	//�Ƴ������б�
	delete list_grid_signed;

	physicsCharaNum--;
}

void PhysicsChara::renewSignedGrids()
{
	//����
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		const Grid* grid = *it;
		grid->list_physics_chara->remove(this);
	}
	list_grid_signed->clear();

	//����ǩ��

	const int x_start = getLeftGrid();
	const int x_end = getRightGrid();
	const int y_start = getTopGrid();
	const int y_end = getBottomGrid();

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			Grid* grid = WorldSystem::getInstance()->getGrid(i, j);
			grid->list_physics_chara->push_back(this);
			list_grid_signed->push_back(grid);
		}
	}
}


void PhysicsChara::update()
{
	//ˢ�³������
	impact = 0;

	//������Ȼ��׹
	if (!moving && moving_inertia <= 0)
	{
		if(detectFalling())
		{
			if(detectForward(PhysicsDirection::down,BlockingType::liquid))
			{
				setMotion(PhysicsDirection::down, low_speed, 1, false);
			}else
			{
				setMotion(PhysicsDirection::down, falling_speed, 1, false);
			}
		}
	}

	//������
	if (moving_inertia <= static_cast<int>(floor(moving_inertia)))
	{
		//׹����
		if (detectFalling())
		{
			falling_count++;
		}
		else
		{
			impact = falling_count;
			falling_count = 0;
		}

		//������ֹ���
		if(hitback&&!moving)
		{
			hitback = false;
		}
	}

	stepForward();
}

void PhysicsChara::stepForward()
{
	if(moving_inertia>0)
	{
		//����λ��-��ȡ��ǰ���ƶ�����
		double decimal_part = moving_inertia - floor(moving_inertia);

		//������
		if (decimal_part <= 0)
		{
			//ײǽ���
			if (detectForward(moving_direction, BlockingType::solid)||detectBorder(moving_direction))
			{
				impact = static_cast<int>(round(moving_inertia));
				moving_inertia = 0;
				moving = false;
			}
			else
			{
				decimal_part = 1;
			}
		}
		//����λ��-����
		
		double step;//����ƶ��ľ���
		if (moving_speed > decimal_part)
		{
			step = decimal_part;
			moving_inertia -= step;
		}
		else
		{
			step = moving_speed;
			moving_inertia -= moving_speed;
		}


		switch (moving_direction)
		{
		case PhysicsDirection::right:
			X += step;
			break;
		case PhysicsDirection::up:
			Y -= step;
			break;
		case PhysicsDirection::left:
			X -= step;
			break;
		case PhysicsDirection::down:
			Y += step;
			break;
		}

		if(moving_inertia<=0)
		{
			moving = false;
		}
	}

	//ˢ��λ��ǩ��
	renewSignedGrids();
}


bool PhysicsChara::detectSubmersed() const
{
	const int x_start = getLeftGrid();
	const int x_end = getRightGrid();
	const int y_start = getTopGrid();
	const int y_end = getBottomGrid();

	for (int i = x_start; i <= x_end; ++i)
	{
		for (int j = y_start; j <= y_end; ++j)
		{
			const Grid* grid = WorldSystem::getInstance()->getGrid(i, j);
			if (!grid->getBlockingType(BlockingType::liquid))
			{
				return false;
			}
		}
	}
	return true;
}

bool PhysicsChara::detectFalling()
{
	if(can_fly)
	{
		return false;
	}else
	{
		if(detectLocal(BlockingType::support)||
			detectForward(PhysicsDirection::down,BlockingType::support)||
			detectForward(PhysicsDirection::down,BlockingType::solid))
		{
			return false;
		}else
		{
			if(can_swim)
			{
				if(detectSubmersed())
				{
					return false;
				}else
				{
					return true;
				}
			}else
			{
				return true;
			}
		}
	}
}


bool PhysicsChara::detectLocal(BlockingType blocking)
{
	for (auto i = list_grid_signed->begin(); i != list_grid_signed->end(); ++i)
	{
		if ((*i)->getBlockingType(blocking))
		{
			return true;
		}
	}
	return false;
}

bool PhysicsChara::detectMoving(PhysicsDirection direction)
{
	if(detectForward(direction,BlockingType::solid))
	{
		return false;
	}

	if (direction == PhysicsDirection::up)
	{
		if (can_fly)
		{
			return true;
		}
		else
		{
			if (detectLocal(BlockingType::support))
			{
				return true;
			}
			else
			{
				if (detectForward(PhysicsDirection::up, BlockingType::liquid))
				{
					return can_swim;
				}
				else
				{
					return false;
				}
			}
		}
	}
	else return true;
}


void PhysicsChara::setMotion(PhysicsDirection direction, double speed, double inertia, bool _hit_back)
{
#ifdef _DEBUG
	if(inertia<0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR,u8"PhysicsChara::setMotion�����˶���С��0");
	}
#endif

	if(!_hit_back)
	{
		//���ǻ���Ч��
		if (moving)
		{
			//�����˶�
		}else
		{
			//û�����˶�
			if(detectMoving(direction))
			{
				moving_speed = speed;
				moving_direction = direction;
				moving_inertia = inertia;
				moving = true;
			}
		}
	}else
	{
		if(steady)
		{
			//���ɻ���
		}else
		{
			//�ɻ���
			hitback = true;
			if (!moving)
			{
				//û�����˶�
				moving_speed = speed;
				moving_direction = direction;
				moving_inertia = inertia;
				moving = true;
			}else
			{
				//���˶���

				const auto j = abs(static_cast<int>(direction) - static_cast<int>(moving_direction));
				if (j==0)
				{
					//ͬ����
					if(moving_speed<speed)
					{
						moving_speed = speed;
					}
					moving_inertia += inertia;
				}else if (j==2)
				{
					//�����ĳ��
					impact = static_cast<int>(floor(moving_inertia)) + falling_count;
					falling_count = 0;
					//������
					moving_direction = direction;
					moving_speed = speed;

					const double decimal_part = moving_inertia - floor(moving_inertia);

					moving_inertia = inertia - decimal_part;

				}else
				{
					//�����ĳ��
					impact = static_cast<int>(floor(moving_inertia)) + falling_count;
					falling_count = 0;
					//��ֱ����
					const double decimal_part = moving_inertia - floor(moving_inertia);

					switch (moving_direction)
					{
					case PhysicsDirection::right:
						X += decimal_part;
						moving_inertia = 0;
						break;
					case PhysicsDirection::up:
						Y -= decimal_part;
						moving_inertia = 0;
						break;
					case PhysicsDirection::left:
						X -= decimal_part;
						moving_inertia = 0;
						break;
					case PhysicsDirection::down:
						Y += decimal_part;
						moving_inertia = 0;
						break;
					}

					moving_speed = speed;
					moving_direction = direction;
					moving_inertia = inertia;
				}
			}
		}
	}
}

void PhysicsChara::setPosition(int x, int y)
{
	X = x;
	Y = y;

	moving = false;
	hitback = false;

	moving_speed = 0;
	moving_inertia = 0;
	moving_direction = PhysicsDirection::right;

	impact = 0;
	falling_count = 0;

	renewSignedGrids();
}


bool PhysicsChara::setDirection(PhysicsDirection direction)
{
	if (moving)return false;
	else
	{
		this->moving_direction = direction;
		return true;
	}
}


PhysicsDirection PhysicsChara::getDirection()const
{
	return moving_direction;
}

bool PhysicsChara::getIfMoving() const
{
	return moving;
}

bool PhysicsChara::getIfFalling() const
{
	return falling_count > 0;
}

bool PhysicsChara::getIfHitBack() const
{
	return hitback;
}

int PhysicsChara::getImpact() const
{
	return impact;
}

double PhysicsChara::getSpeed() const
{
	return moving_speed;
}


int PhysicsChara::physicsCharaNum = 0;

int PhysicsChara::getPhysicsCharaNum()
{
	return physicsCharaNum;
}
