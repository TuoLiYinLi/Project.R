#pragma once
#include "abstract_inspect_target.h"
#include "CountingContainer.h"
#include "GameObject.h"
#include "PhysicsFacility.h"

enum class FacilityState
{
	idle,
	activated,
	dead
};

class Facility :
	public GameObject,public abstract_inspect_target
{
public:
	static Facility* createNew();

	void update() override;

	SDL_Texture* getThumbnail() override;
	std::wstring getBrief() override;

	std::wstring getMainInfo() override;
	std::wstring getDataInfo() override;
	std::wstring getExtraInfo() override;

protected:
	std::wstring science_name;//ѧ��
	std::wstring introduction;//������Ϣ
protected:

	FacilityState state;	//��ʩ��״̬
	int animation_progress;	//��ǰ��������

	//��ʩ�Ķ���
	int animation_length_idle;	//ͣ�Ͷ�����ʱ��,0����û�ж���
	int animation_length_activated;	//�������ʱ��,0����û�ж���
	int animation_length_dead;	//����������ʱ��,0����û�ж���

	int activate_length;
	int activate_CD;

	int delay_activate;//�����ҡ

	AnimationType animation_type_idle;//���ö���
	AnimationType animation_type_activated;//�����
	AnimationType animation_type_dead;//��������
public:
	//��ʩ������
	int health;	//һ����ʩ������ֵ
	int health_max;//��ʩ���������ֵ

	//��ʩ�ļ�����
	CountingContainer* counting_container;//����������

protected:
	//�����ӿ�
	virtual void onIdle();//������״̬ʱ ÿ֡����
	virtual void onActivate();//������������ʹ��ʱ ���̴���
	virtual void onKill();//������ֵ����ʱ ���̴���
	virtual void onDead();//����������ʧʱ ���̴���
	virtual void onHit();//���ܵ�Ͷ����ֱ���˺�ʱ ���̴���

	RenderingAnimation* getRenderingAnimation()const;
	PhysicsFacility* getPhysicsFacility()const;
public:
	void setPosition(int x, int y);//���ͽ�ɫ������λ��
	static int getFacilityNum();

protected:
	Facility();
	~Facility() override;

	void update_animation();//���¶���
	void sync_animation()const;//ͬ������
	void update_depth()const;

	void setAnimationIdle();//����Ϊ���ö���
	void setAnimationActivate();//����Ϊ�����
	void setAnimationDead();//����Ϊ��������

private:
	static int facility_num;
};

