#pragma once
#include <list>
#include <string>

class Chara;

enum class GeneTag
{
	double_health,//˫������
	double_health_recovery,//˫������
	double_stamina,//˫������
	double_attack,//˫��������
	double_growth,//˫���ɳ�
	corruption_disease,//�����缲
	projectile_copy,//����Ͷ����

	sludge_essence,//���ྫ��
	corrupted_content,//����������
	slime_glue,//ʷ��ķ��
	slime_recombination_core,//ʷ��ķ�����
	slime_corruption_core,//ʷ��ķ������
};

enum class OverrideOperation
{
	override_false = false,
	override_true = true, 
	stay_original,//����ԭ״
};

//������ �����ڻ���������
class Gene
{
public:
	static Gene* CreateNew();
	void destroy() const;

	//��ֵ��������

	std::wstring name;//��������
	double extra_speed;//�����ƶ��ٶ�
	int extra_health;//��������ֵ
	double extra_health_recovery;//���������ָ�
	int extra_stamina;//��������
	double extra_stamina_recovery;//���������ָ�
	OverrideOperation water_stifled;//�Ƿ�ˮ�º�������
	OverrideOperation injured_on_impact;//�����������
	OverrideOperation injured_on_burning;//ȼ����������
	OverrideOperation injured_on_poisoned;//ȼ����������

	//�ؼ��ʲ���

	std::list<GeneTag> tags;//�����ǩ/�ؼ���

	//����Ч������

	void trigger_onEveryTime(Chara* chara)const;
	void trigger_onIdle(Chara* chara) const;
	void trigger_onMoving(Chara* chara) const;
	void trigger_onBasicSkill(Chara* chara) const;
	void trigger_onSpecialSkill(Chara* chara) const;
	void trigger_onKill(Chara* chara) const;
	void trigger_onDead(Chara* chara) const;
	void trigger_onVanish(Chara* chara) const;
	void trigger_onImpact(Chara* chara) const;
	void trigger_onBurning(Chara* chara) const;
	void trigger_onPoisoned(Chara* chara) const;
	void trigger_onHit(Chara* chara) const;

	//������Ļص�����

	void(*callback_onEveryTime)(Chara* chara);
	void(*callback_onIdle)(Chara* chara);
	void(*callback_onMoving)(Chara* chara);
	void(*callback_onBasicSkill)(Chara* chara);
	void(*callback_onSpecialSkill)(Chara* chara);
	void(*callback_onKill)(Chara* chara);
	void(*callback_onDead)(Chara* chara);
	void(*callback_onVanish)(Chara* chara);
	void(*callback_onImpact)(Chara* chara);
	void(*callback_onBurning)(Chara* chara);
	void(*callback_onPoisoned)(Chara* chara);
	void(*callback_onHit)(Chara* chara);

	bool operator<(Gene tar);//������������

	static int getGeneNum();//��ȡ����ռ���ڴ��Gene
	
protected:
	static int gene_num;
	Gene();
	virtual ~Gene();

public:
	//��̬������Ĵ�������

	//�ָ�1����ֵ
	static void recover1HP(Chara* chara);
	//����һ��������ը
	static void projectileCorruptionBurst(Chara* chara);
	//����ճҺ����ָ�st
	static void recoverSTNearMucus(Chara* chara);
	//���˽�ˮ,�������˼���st
	static void enemySTGlue(Chara* chara);
	
};


class GeneMaker
{
public:
	
	static Gene* random_slime_related();

	static Gene* sludge_essence();
	static Gene* slime_inhabit();
	static Gene* slime_glue();
	static Gene* slime_recombination_core();
	static Gene* slime_corruption_core();
	static Gene* corruption_enchantment();

};


//�ۺ��� ����������
class integration_gene_container
{
public:
	integration_gene_container();
	integration_gene_container(Chara* _host);

	void setHost(Chara* chara);

	//�������

	void addGene(Gene* g);//����µĻ���
	void removeGene(Gene* g);//�Ƴ����л���
	void transGeneTo(Gene* g, integration_gene_container* container);//������ת�Ƶ���������

	//��������

	void sort();//�Ի����������
	void setCapacity(unsigned long long num);//��������
	unsigned long long getCapacity() const;//��ȡ������С
	unsigned long long getNum() const;//��ȡ����
	std::list<std::wstring> getGeneNameList();//��ȡ�ڲ�����������б�

	//��ȡ����

	bool getGeneTag(GeneTag t);//Ѱ�Ҷ�Ӧ�ؼ���
	double getExtraSpeed();//�����ƶ��ٶ�����
	int getExtraHealth();//��������ֵ����
	double getExtraHealthRecovery();//���������ָ�����
	int getExtraStamina();//�������ֵ����
	double getExtraStaminaRecovery();//��������ָ�����

	OverrideOperation getWaterStifled();//�Ƿ�ˮ����Ϣ����
	OverrideOperation getInjuredOnImpact();//�����������
	OverrideOperation getInjuredOnBurning();//�����������
	OverrideOperation getInjuredOnPoisoned();//�����������

	//����Ч��

	void triggerOnEveryTime();
	void triggerOnIdle();
	void triggerOnMoving();
	void triggerOnBasicSkill();
	void triggerOnSpecialSkill();
	void triggerOnKill();
	void triggerOnDead();
	void triggerOnVanish();
	void triggerOnImpact();
	void triggerOnBurning();
	void triggerOnPoisoned();
	void triggerOnHit();

protected:
	Chara* host = nullptr;
	std::list<Gene*> contents;//����Ļ�������
	unsigned long long capacity;
};

