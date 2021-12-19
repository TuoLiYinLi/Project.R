#include "PhysicsChara.h"
#include "WorldSystem.h"
#include "SDL.h"
#include "Defined.h"

PhysicsChara* PhysicsChara::createNew()
{
	PhysicsChara* physics_chara = new PhysicsChara();
	if(!physics_chara)
	{
		SDL_Log(u8"���� ����physics_chara�ڴ治��");
	}
	return physics_chara;
}

PhysicsChara::PhysicsChara()
{
	//��ʼ������
	type_physics = PhysicsType::chara;

	can_fly = false;
	can_swim = false;

	impact = 0;

	moving = false;
	steady = false;

	moving_speed = 0;
	moving_direction = CharaDirection::right;
	moving_inertia = 0;

	falling_count = 0;

	//���Լ���ӵ���ɫ�����б�
	WorldSystem::getInstance()->list_physics_chara->push_front(this);
	//��ʼ��ǩ�������б�
	list_grid_signed = new std::list<Grid*>();


}

PhysicsChara::~PhysicsChara()
{
	//���Լ��ӽ�ɫ�����б��Ƴ�
	WorldSystem::getInstance()->list_physics_chara->remove(this);
	//�Ƴ������б�
	delete list_grid_signed;
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
				impact = (int)round(moving_inertia);
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
		case CharaDirection::right:
			X += step;
			break;
		case CharaDirection::up:
			Y -= step;
			break;
		case CharaDirection::left:
			X -= step;
			break;
		case CharaDirection::down:
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

int PhysicsChara::getImpact() const
{
	return impact;
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
			setMotion(CharaDirection::down, FALLING_SPEED, 1, false);
		}
	}

	//������
	if (moving_inertia <= (int)floor(moving_inertia))
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
	}

	stepForward();
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
			const Grid* grid = WorldSystem::getInstance()->map->at(i)->at(j);
			if (!grid->getBlockingType(BlockingType::liquid))
			{
				return false;
			}
		}
	}
	return true;
}


bool PhysicsChara::detectFalling() const
{
	if(can_fly)
	{
		return false;
	}else
	{
		if(detectLocal(BlockingType::support)||
			detectForward(CharaDirection::down,BlockingType::support)||
			detectForward(CharaDirection::down,BlockingType::solid))
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




bool PhysicsChara::detectForward(CharaDirection direction, BlockingType blocking) const
{
	int x_start=0, x_end=0,
		y_start=0, y_end=0;
	switch (direction)
	{
	case CharaDirection::right:
		x_start = getRightGrid() + 1;
		x_end = x_start;
		y_start = getTopGrid();
		y_end = getBottomGrid();
		break;
	case CharaDirection::up:
		x_start = getLeftGrid();
		x_end = getRightGrid();
		y_start = getTopGrid() - 1;
		y_end = y_start;
		break;
	case CharaDirection::left:
		x_start = getLeftGrid() - 1;
		x_end = x_start;
		y_start = getTopGrid();
		y_end = getBottomGrid();
		break;
	case CharaDirection::down:
		x_start = getLeftGrid();
		x_end = getRightGrid();
		y_start = getBottomGrid() + 1;
		y_end = y_start;
		break;
	}

	if(detectBorder(direction))
	{
		return false;
	}

	for (int i = x_start; i <= x_end; i++)
	{
		for (int j = y_start; j <= y_end; j++)
		{
			const Grid* grid = WorldSystem::getInstance()->map->at(i)->at(j);
			if(grid->getBlockingType(blocking))
			{
				return true;
			}
		}
	}
	return false;
}

bool PhysicsChara::detectBorder(CharaDirection direction) const
{
	switch (direction)
	{
	case CharaDirection::right:
		return getRightGrid() + 1 >= (int)WORLD_WIDTH;
	case CharaDirection::up:
		return getTopGrid() - 1 < 0;
	case CharaDirection::left:
		return getLeftGrid() - 1 < 0;
	case CharaDirection::down:
		return getBottomGrid() + 1 >= (int)WORLD_HEIGHT;
	}

	return false;
}


bool PhysicsChara::detectLocal(BlockingType blocking) const
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

bool PhysicsChara::detectMoving(CharaDirection direction) const
{
	if(detectForward(direction,BlockingType::solid))
	{
		return false;
	}

	if (direction == CharaDirection::up)
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
				if (detectForward(CharaDirection::up, BlockingType::liquid))
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


void PhysicsChara::setMotion(CharaDirection direction, double speed, double inertia, bool hit_back)
{
	if(inertia<0)
	{
		SDL_Log(u8"���� �����˶���С��0");
	}

	if(!hit_back)
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

				const auto j = abs(int(direction) - int(moving_direction));
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
					impact = (int)floor(moving_inertia) + falling_count;
					falling_count = 0;
					//������
					moving_direction = direction;
					moving_speed = speed;

					const double decimal_part = moving_inertia - floor(moving_inertia);

					moving_inertia = inertia - decimal_part;

				}else
				{
					//�����ĳ��
					impact = (int)floor(moving_inertia) + falling_count;
					falling_count = 0;
					//��ֱ����
					const double decimal_part = moving_inertia - floor(moving_inertia);

					switch (moving_direction)
					{
					case CharaDirection::right:
						X += decimal_part;
						moving_inertia = 0;
						break;
					case CharaDirection::up:
						Y -= decimal_part;
						moving_inertia = 0;
						break;
					case CharaDirection::left:
						X -= decimal_part;
						moving_inertia = 0;
						break;
					case CharaDirection::down:
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
			Grid* grid = WorldSystem::getInstance()->map->at(i)->at(j);
			grid->list_physics_chara->push_back(this);
			list_grid_signed->push_back(grid);
		}
	}
}

bool PhysicsChara::getSteady() const
{
	return steady;
}

bool PhysicsChara::getMoving() const
{
	return moving;
}
