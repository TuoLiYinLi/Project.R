#pragma once
#include <list>
#include <string>

class Chara;

enum class GeneTag
{
	double_health,//双倍生命
	double_health_recovery,//双倍愈合
	double_stamina,//双倍活力
	double_attack,//双倍攻击力
	double_growth,//双倍成长
	corruption_disease,//腐化顽疾
	projectile_copy,//复制投射物

	sludge_essence,//淤泥精髓
	corrupted_content,//腐化内容物
	slime_glue,//史莱姆胶
	slime_recombination_core,//史莱姆重组核
	slime_corruption_core,//史莱姆腐化核
};

enum class OverrideOperation
{
	override_false = false,
	override_true = true, 
	stay_original,//保持原状
};

//基因类 存在于基因容器中
class Gene
{
public:
	static Gene* CreateNew();
	void destroy() const;

	//数值修正部分

	std::wstring name;//基因名称
	double extra_speed;//修正移动速度
	int extra_health;//修正生命值
	double extra_health_recovery;//修正生命恢复
	int extra_stamina;//修正活力
	double extra_stamina_recovery;//修正活力恢复
	OverrideOperation water_stifled;//是否水下呼吸修正
	OverrideOperation injured_on_impact;//冲击受伤修正
	OverrideOperation injured_on_burning;//燃烧受伤修正
	OverrideOperation injured_on_poisoned;//燃烧受伤修正

	//关键词部分

	std::list<GeneTag> tags;//基因标签/关键词

	//触发效果部分

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

	//可重组的回调函数

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

	bool operator<(Gene tar);//基因排序依据

	static int getGeneNum();//获取所有占用内存的Gene
	
protected:
	static int gene_num;
	Gene();
	virtual ~Gene();

public:
	//静态可重组的触发函数

	//恢复1生命值
	static void recover1HP(Chara* chara);
	//产生一个腐化爆炸
	static void projectileCorruptionBurst(Chara* chara);
	//靠近粘液额外恢复st
	static void recoverSTNearMucus(Chara* chara);
	//敌人胶水,附近敌人减少st
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


//聚合类 基因容器类
class integration_gene_container
{
public:
	integration_gene_container();
	integration_gene_container(Chara* _host);

	void setHost(Chara* chara);

	//基因操作

	void addGene(Gene* g);//添加新的基因
	void removeGene(Gene* g);//移除已有基因
	void transGeneTo(Gene* g, integration_gene_container* container);//将基因转移到其它容器

	//容器设置

	void sort();//对基因进行排序
	void setCapacity(unsigned long long num);//设置容量
	unsigned long long getCapacity() const;//获取容量大小
	unsigned long long getNum() const;//获取数量
	std::list<std::wstring> getGeneNameList();//获取内部基因的名字列表

	//获取数据

	bool getGeneTag(GeneTag t);//寻找对应关键词
	double getExtraSpeed();//计算移动速度修正
	int getExtraHealth();//计算生命值修正
	double getExtraHealthRecovery();//计算生命恢复修正
	int getExtraStamina();//计算活力值修正
	double getExtraStaminaRecovery();//计算活力恢复修正

	OverrideOperation getWaterStifled();//是否水下窒息修正
	OverrideOperation getInjuredOnImpact();//冲击受伤修正
	OverrideOperation getInjuredOnBurning();//冲击受伤修正
	OverrideOperation getInjuredOnPoisoned();//冲击受伤修正

	//触发效果

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
	std::list<Gene*> contents;//储存的基因内容
	unsigned long long capacity;
};

