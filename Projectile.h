#pragma once
#include "GameObject.h"

//��Ϸ���� Ͷ���� ����ʵ����
class Projectile:
	public GameObject
{
public:
	void update() override;//������Ϊ

	RenderingAnimation* getRenderingAnimation()const;
	
	static int getProjectileNum();
protected:
	Projectile();
	~Projectile() override;

	void sync_animation()const;
	void sync_flip()const;
	void update_depth()const;

	int animation_length;	//ѭ��һ�ζ�����ʱ��
	int animation_progress;	//��������
	AnimationType animation_type;//����

	int life_time;	//�ܹ������ʱ��

private:
	static int projectile_num;
};

