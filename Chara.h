#pragma once
#include "GameObject.h"
#include "abstract_inspect_target.h"

#include "PhysicsChara.h"

#include "CountingContainer.h"
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

	std::wstring getBrief() override;
	SDL_Texture* getThumbnail() override;

	std::wstring getMainInfo() override;
	std::wstring getDataInfo() override;
	std::wstring getExtraInfo() override;
	
protected:
	std::wstring science_name;//ѧ��
	std::wstring introduction;//������Ϣ

	PhysicsChara* getPhysicsChara() const;
	RenderingAnimation* getRenderingAnimation()const;

protected:
	CharaActionType action_type;//����ʹ�õĶ�������

	//��ɫ�Ķ���
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

public:
	//��ɫ������

	double moving_speed;

	int health_max;//�������ֵ
	int health;//����ֵ
	double health_recovery_speed;//����ֵ�ָ��ٶ�
	double health_recovery_accumulation;//����ֵ�ָ�������

	double burning_damage_accumulation;//ȼ�ղ������ۻ��˺�
	double poisoned_damage_accumulation;//�ж��������ۻ��˺�
	double oxygen_damage_accumulation;//ȱ�������ۻ��˺�

	int stamina_max;//������ֵ
	int stamina;//����ֵ
	double stamina_recovery_speed;//����ֵ�ָ��ٶ�
	double stamina_recovery_accumulation;//����ֵ�ۻ���
	
	int oxygen;//����ֵ

	//��ɫ�ļ�����
	CountingContainer* counting_container;//����������


	//��ɫЧ��
	int effect_charging;// ����Ч��ʱ��
	int effect_resistant;// �ֿ�Ч��ʱ��
	int effect_poisoned;// �ж�Ч��ʱ��
	int effect_burning;// ȼ��Ч��ʱ��
	int effect_sealed;// ��ӡЧ��ʱ��
	int effect_blind;// äĿЧ��ʱ��
	int effect_dizzy;// ѣ��Ч��ʱ��

	bool setDirection(CharaDirection d) const;//���ý�ɫ����
	void setPosition(int x, int y);//���ͽ�ɫ������λ��

	void actMove(CharaDirection d); //�����ƶ�
	virtual void actSkillSpecial(CharaDirection d);//ʹ����������
	virtual void actSkillBasic(CharaDirection d);//ʹ�û�������

protected:
	//�����ӿ�
	virtual void onIdle();//������״̬ʱ ÿ֡����
	virtual void onMoving();//���ƶ�״̬ʱ ÿ֡����
	virtual void onBasicSkill();//������������ʹ��ʱ ���̴���
	virtual void onSpecialSkill();//������������ʹ��ʱ ���̴���
	virtual void onKill();//������ֵ����ʱ ���̴���
	virtual void onDead();//����������ʧʱ ���̴���
	virtual void onImpact(int _impact);//���ܵ��ⲿ���ʱ ���̴���
	virtual void onHit();//���ܵ�Ͷ����ֱ���˺�ʱ ���̴���
	virtual void onBurning();//���Լ�ȼ��ʱ ÿ֡����
	virtual void onPoisoned();//���Լ��ж�ʱ ÿ֡����
	//��ɫ���ƽӿ�
	virtual void decide_action();//����ɫ����ʱ,ֱ�Ӿ�����һ������

public:
	static int getCharaNum();

protected:
	Chara();
	~Chara() override;

	static int chara_num;

	void update_attributes();//������������
	void update_effect();//����Ч��
	void update_animation();//�ƽ��������ݱ仯
	void sync_animation();//������������ͬ��
	void update_depth()const;//���¶���Ԫ�������


	bool getIfDisturbed() const;//���ϱ����״̬������
	bool getIfMoving() const;//�����ƶ�״̬������

	void setAnimationIdle();//����Ϊ���ö���
	void setAnimationMoving();//����Ϊ�ƶ�����
	void setAnimationDisturbed();//����Ϊ���䶯��
	void setAnimationSkillSpecial();//����Ϊ������������
	void setAnimationSkillBasic();//����Ϊ��ͨ��������
	void setAnimationDead();//����Ϊ��������

};

