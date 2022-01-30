#pragma once
class GameObject;

enum class PhysicsType
{
	none,	//空
	chara,	//角色物理
	facility,	//设施物理
	projectile,	//投射物物理
};

enum class BlockingType
{
	air,	//无阻挡,空气
	support,	//半阻挡,支撑
	solid,	//全阻挡,固态
	liquid,	//液态
};

enum class AllyType
{
	monster,//怪物阵营
	warrior,//勇者阵营
	neutral,//中立阵营
	peace,//和平阵营
};

class PhysicsObject
{
public:
	virtual void destroy();	//销毁自己

	virtual void update();	//更新帧

	double X, Y;	//自身的X、Y坐标
	int bodyX, bodyY;	//模拟碰撞体积的大小，向右下方延申

	AllyType type_ally;//所属的阵营
	GameObject* game_object;	//绑定的游戏对象
	PhysicsType getPhysicsType() const;	//获取物理种类

	double getTop() const;	//获取顶部高度
	double getBottom() const;	//获取底部坐标
	double getLeft() const;	//获取左边坐标
	double getRight() const;	//获取右边坐标

	int getTopGrid() const;	//获取顶部占据的网格
	int getBottomGrid() const;	//获取底部占据的网格
	int getLeftGrid() const;	//获取左部占据的网格
	int getRightGrid() const;	//获取右部占据的网格

	virtual void setPosition(int x, int y);//设置(传送)位置

	virtual void renewSignedGrids();	//对地图签入自己的位置

	static int getPhysicsObjectNum();
protected:
	PhysicsObject();	//不允许外部实例化
	virtual ~PhysicsObject();	//为了继承自我并且保证销毁释放内存,必须虚析构函数

	PhysicsType type_physics;	//物理类型

	static int physicsObjectNum;

};

