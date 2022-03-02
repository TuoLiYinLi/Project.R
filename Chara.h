#pragma once
#include "GameObject.h"
#include "abstract_inspect_target.h"

#include "PhysicsChara.h"

#include "idea_particle_dizzy.h"
#include "idea_particle_flame.h"
#include "idea_particle_healing.h"
#include "idea_particle_poisoned.h"

#include "integrate_particles_maker.h"
#include "integration_counting_container.h"
#include "integration_gene_container.h"

class Projectile;

//ö�� ��ɫ�ж�״̬
enum class CharaActionType
{
	idle,//����
	moving,//�ƶ�
	skill_basic,//��������
	skill_special,//���⼼��
	disturbed,//�����
	dead,//����
};

//��Ϸ���� ��ɫ 
class Chara :
	public GameObject,public abstract_inspect_target
{
public:
	static Chara* createNew();
	void update() override;

	PhysicsChara* getPhysics() const;
	RenderingAnimation* getRenderingAnimation()const;
	//�ⲿ���ýӿ�

	std::wstring getBrief() override;
	SDL_Texture* getThumbnail() override;
	std::wstring getMainInfo() override;
	std::wstring getDataInfo() override;
	std::wstring getExtraInfo() override;

	virtual void onHit(Projectile* p);//���ܵ�Ͷ����ֱ���˺�ʱ ���̴���
	virtual void onKill(Chara* who);//����Ͷ����ɹ�ɱ����ʱ ���̴���

	bool setDirection(PhysicsDirection d) const;//���ý�ɫ����
	void setPosition(int x, int y);//���ͽ�ɫ������λ��

	void actMove(PhysicsDirection d); //�����ƶ�
	virtual void actSkillSpecial(PhysicsDirection d);//ʹ����������
	virtual void actSkillBasic(PhysicsDirection d);//ʹ�û�������

	//��ɫ������

	double moving_speed;//��ɫ�ƶ��ٶ�
	double real_moving_speed();//��ɫ�ƶ��ٶ�

	int health_max;//�������ֵ
	int real_health_max();//�������ֵ

	int health;//����ֵ
	double health_recovery_speed;//����ֵ�ָ��ٶ�
	double real_health_recovery_speed();//����ֵ�ָ��ٶ�
	double health_recovery_accumulation;//����ֵ�ָ�������

	double burning_damage_accumulation;//ȼ�ղ������ۻ��˺�
	double poisoned_damage_accumulation;//�ж��������ۻ��˺�
	double oxygen_damage_accumulation;//ȱ�������ۻ��˺�

	int stamina_max;//������ֵ
	int real_stamina_max();//������ֵ
	int stamina;//����ֵ
	double stamina_recovery_speed;//����ֵ�ָ��ٶ�
	double real_stamina_recovery_speed();//����ֵ�ָ��ٶ�
	double stamina_recovery_accumulation;//����ֵ�ۻ���

	int skill_basic_cost;//����������st����
	int skill_special_cost;//����������st����

	bool water_stifled;//�Ƿ���ˮ����Ϣ
	int oxygen;//����ֵ

	bool injured_on_burning;//ȼ��ʱ�Ƿ�����
	bool injured_on_impact;//�ܵ����ʱ�Ƿ�����
	bool injured_on_poisoned;//�ж�ʱ�Ƿ�����

	//��ɫЧ��

	int effect_charging;// ����Ч��ʱ��
	int effect_resistant;// �ֿ�Ч��ʱ��
	int effect_poisoned;// �ж�Ч��ʱ��
	int effect_burning;// ȼ��Ч��ʱ��
	int effect_sealed;// ��ӡЧ��ʱ��
	int effect_blind;// äĿЧ��ʱ��
	int effect_dizzy;// ѣ��Ч��ʱ��
	integration_counting_container counting_container;//����������
	integration_gene_container gene_container;//��������

	static int getCharaNum();//��ȡ��Ծ��ɫ����

protected:
	Chara();
	~Chara() override;

	std::wstring science_name;//ѧ��
	std::wstring introduction;//������Ϣ

	//��ɫ�Ķ���
	
	CharaActionType action_type;//����ʹ�õĶ�������

	int animation_progress;//��ǰ��������
	int animation_length_idle;//ͣ�Ͷ�����ʱ��,0����û�ж���
	int animation_length_moving;//�������ʱ��,0����û�ж���
	int animation_length_disturbed;//��϶�����ʱ��,0����û�ж���
	int animation_length_skill_basic;//������������ʱ��,0����û�ж���
	int animation_length_skill_special;//������������ʱ��,0����û�ж���
	int animation_length_dead;//����������ʱ��,0����û�ж���

	int delay_skill_basic;//���������Ĵ�������
	int delay_skill_special;//���������Ĵ�������

	AnimationType animation_type_idle;//���ö���
	AnimationType animation_type_moving;//�ƶ�����
	AnimationType animation_type_disturbed;//���䶯��
	AnimationType animation_type_skill_basic;//�������ܶ���
	AnimationType animation_type_skill_special;//���⼼�ܶ���
	AnimationType animation_type_dead;//��������

	//�����ӿ�

	virtual void onEveryTime();//�κ�ʱ��ÿ֡����
	virtual void onIdle();//������״̬ʱ ÿ֡����
	virtual void onMoving();//���ƶ�״̬ʱ ÿ֡����
	virtual void onBasicSkill();//������������ʹ��ʱ ���̴���
	virtual void onSpecialSkill();//������������ʹ��ʱ ���̴���
	virtual void onDead();//������ֵ����ʱ ���̴���
	virtual void onVanish();//����������ʧʱ ���̴���
	virtual void onImpact(int _impact);//���ܵ��ⲿ���ʱ ���̴���
	virtual void onBurning();//���Լ�ȼ��ʱ ÿ֡����
	virtual void onPoisoned();//���Լ��ж�ʱ ÿ֡����
	virtual void decide_action();//����ɫ����ʱ,ֱ�Ӿ�����һ������

	//�ж�����

	bool checkDisturbed() const;//���ϱ����״̬������
	bool checkMoving() const;//�����ƶ�״̬������
	bool checkStifled();//�Ƿ���Ϣ
	bool checkInjuredOnBurning();//����Ƿ���Ϊȼ�ն��ܵ��˺�
	bool checkInjuredOnPoisoned();//����Ƿ���Ϊ�ж����ܵ��˺�
	bool checkInjuredOnImpact();//����Ƿ���Ϊ������ܵ��˺�

	//��������

	void update_attributes();//������������
	void update_effect();//����Ч��
	void update_animation();//�ƽ��������ݱ仯
	void sync_animation();//������������ͬ��
	void update_depth()const;//���¶���Ԫ�������
	void update_damaged_highlight();//�����ܻ���ɫ
	int damaged_highlight;//���˲�����ɫ����

	void setAnimationIdle();//����Ϊ���ö���
	void setAnimationMoving();//����Ϊ�ƶ�����
	void setAnimationDisturbed();//����Ϊ���䶯��
	void setAnimationSkillSpecial();//����Ϊ������������
	void setAnimationSkillBasic();//����Ϊ��ͨ��������
	void setAnimationDead();//����Ϊ��������

	//����������

	integrate_particles_maker<idea_particle_poisoned> pm_poisoned;
	integrate_particles_maker<idea_particle_flame> pm_burning;
	integrate_particles_maker<idea_particle_dizzy> pm_dizzy;
	integrate_particles_maker<idea_particle_healing> pm_healing;
	
	static int chara_num;
};

