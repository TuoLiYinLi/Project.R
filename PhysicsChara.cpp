#include "PhysicsChara.h"
#include "WorldSystem.h"
#include "SDL.h"
#include "Defined.h"

PhysicsChara* PhysicsChara::createNew()
{
	PhysicsChara* physics_chara = new PhysicsChara();
	if(!physics_chara)
	{
		SDL_Log(u8"警告 分配physics_chara内存不足");
	}
	return physics_chara;
}

PhysicsChara::PhysicsChara()
{
	//初始化数据
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

	//将自己添加到角色物理列表
	WorldSystem::getInstance()->list_physics_chara->push_front(this);
	//初始化签入网格列表
	list_grid_signed = new std::list<Grid*>();


}

PhysicsChara::~PhysicsChara()
{
	//将自己从角色物理列表移除
	WorldSystem::getInstance()->list_physics_chara->remove(this);
	//移除网格列表
	delete list_grid_signed;
}

void PhysicsChara::stepForward()
{
	if(moving_inertia>0)
	{
		//更新位置-获取当前的移动距离
		double decimal_part = moving_inertia - floor(moving_inertia);

		//整点检查
		if (decimal_part <= 0)
		{
			//撞墙检查
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
		//更新位置-步进
		
		double step;//这次移动的距离
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

	//刷新位置签入
	renewSignedGrids();
}

int PhysicsChara::getImpact() const
{
	return impact;
}


void PhysicsChara::update()
{
	//刷新冲击数据
	impact = 0;

	//发生自然下坠
	if (!moving && moving_inertia <= 0)
	{
		if(detectFalling())
		{
			setMotion(CharaDirection::down, FALLING_SPEED, 1, false);
		}
	}

	//整点检查
	if (moving_inertia <= (int)floor(moving_inertia))
	{
		//坠落检查
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
		SDL_Log(u8"警告 设置运动量小于0");
	}

	if(!hit_back)
	{
		//不是击退效果
		if (moving)
		{
			//正在运动
		}else
		{
			//没有在运动
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
			//不可击退
		}else
		{
			//可击退
			if (!moving)
			{
				//没有在运动
				moving_speed = speed;
				moving_direction = direction;
				moving_inertia = inertia;
				moving = true;
			}else
			{
				//在运动中

				const auto j = abs(int(direction) - int(moving_direction));
				if (j==0)
				{
					//同方向
					if(moving_speed<speed)
					{
						moving_speed = speed;
					}
					moving_inertia += inertia;
				}else if (j==2)
				{
					//产生的冲击
					impact = (int)floor(moving_inertia) + falling_count;
					falling_count = 0;
					//反方向
					moving_direction = direction;
					moving_speed = speed;

					const double decimal_part = moving_inertia - floor(moving_inertia);

					moving_inertia = inertia - decimal_part;

				}else
				{
					//产生的冲击
					impact = (int)floor(moving_inertia) + falling_count;
					falling_count = 0;
					//垂直方向
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
	//重置
	for (auto it = list_grid_signed->begin(); it != list_grid_signed->end(); ++it)
	{
		const Grid* grid = *it;
		grid->list_physics_chara->remove(this);
	}
	list_grid_signed->clear();

	//重新签入

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
