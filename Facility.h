#pragma once
#include "abstract_inspect_target.h"
#include "integration_counting_container.h"
#include "GameObject.h"
#include "PhysicsFacility.h"

class Projectile;

//ö�� ��ʩ״̬
enum class FacilityState
{
	idle,
	activated,
	dead
};

//��Ϸ���� ��ʩ
class Facility :
	public GameObject,public abstract_inspect_target
{
public:
	static Facility* createNew();

	void update() override;

	//�ⲿ���ýӿ�

	SDL_Texture* getThumbnail() override;
	std::wstring getBrief() override;
	std::wstring getMainInfo() override;
	std::wstring getDataInfo() override;
	std::wstring getExtraInfo() override;

	virtual void onHit(Projectile* p);//���ܵ�Ͷ����ֱ���˺�ʱ ���̴���

	void setPosition(int x, int y);//���ͽ�ɫ������λ��

	//��ʩ������

	int health;	//һ����ʩ������ֵ
	int health_max;//��ʩ���������ֵ
	integration_counting_container counting_container;//����������

	static int getFacilityNum();

protected:
	Facility();
	~Facility() override;

	RenderingAnimation* getRendering()const;
	PhysicsFacility* getPhysics()const;

	std::wstring science_name;//ѧ��
	std::wstring introduction;//������Ϣ

	//��ʩ�Ķ���

	FacilityState state;	//��ʩ��״̬
	int animation_progress;	//��ǰ��������
	int animation_length_idle;	//ͣ�Ͷ�����ʱ��,0����û�ж���
	int animation_length_activated;	//�������ʱ��,0����û�ж���
	int animation_length_dead;	//����������ʱ��,0����û�ж���

	int activate_length;
	int activate_CD;

	int delay_activate;//�����ҡ

	AnimationType animation_type_idle;//���ö���
	AnimationType animation_type_activated;//�����
	AnimationType animation_type_dead;//��������
	
	//�����ӿ�

	virtual void onIdle();//������״̬ʱ ÿ֡����
	virtual void onActivate();//������������ʹ��ʱ ���̴���
	virtual void onKill();//������ֵ����ʱ ���̴���
	virtual void onDead();//����������ʧʱ ���̴���

	//��������

	void update_animation();//���¶���
	void sync_animation()const;//ͬ������
	void update_depth()const;
	void update_damaged_highlight();//�����ܻ���ɫ
	int damaged_highlight;//���˲�����ɫ����

	void setAnimationIdle();//����Ϊ���ö���
	void setAnimationActivate();//����Ϊ�����
	void setAnimationDead();//����Ϊ��������
	
	static int facility_num;
};

