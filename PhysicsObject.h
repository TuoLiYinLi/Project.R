#pragma once
class GameObject;

enum class PhysicsType
{
	none,	//��
	chara,	//��ɫ����
	facility,	//��ʩ����
	projectile,	//Ͷ��������
};

enum class BlockingType
{
	air,	//���赲,����
	support,	//���赲,֧��
	solid,	//ȫ�赲,��̬
	liquid,	//Һ̬
};

class PhysicsObject
{
public:
	virtual void destroy();	//�����Լ�

	virtual void update();	//����֡

	double X, Y;	//�����X��Y����
	int bodyX, bodyY;	//ģ����ײ����Ĵ�С�������·�����

	GameObject* game_object;	//�󶨵���Ϸ����
	PhysicsType getPhysicsType() const;	//��ȡ��������

	double getTop() const;	//��ȡ�����߶�
	double getBottom() const;	//��ȡ�ײ�����
	double getLeft() const;	//��ȡ�������
	double getRight() const;	//��ȡ�ұ�����

	int getTopGrid() const;	//��ȡ����ռ�ݵ�����
	int getBottomGrid() const;	//��ȡ�ײ�ռ�ݵ�����
	int getLeftGrid() const;	//��ȡ��ռ�ݵ�����
	int getRightGrid() const;	//��ȡ�Ҳ�ռ�ݵ�����

	virtual void setPosition(int x, int y);//����(����)λ��

	virtual void renewSignedGrids();	//�Ե�ͼǩ���Լ���λ��

protected:
	PhysicsObject();	//�������ⲿʵ����
	virtual ~PhysicsObject();	//Ϊ�˼̳����Ҳ��ұ�֤�����ͷ��ڴ�,��������������

	PhysicsType type_physics;	//��������

};

