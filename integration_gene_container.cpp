#include "integration_gene_container.h"
#include "Chara.h"

//Gene部分

Gene* Gene::CreateNew()
{
	return new Gene();
}

void Gene::destroy() const
{
	delete this;
}

Gene::Gene()
{
	name = L"默认基因";
	extra_speed = 0;
	extra_health = 0;
	extra_health_recovery = 0;
	extra_stamina = 0;
	extra_stamina_recovery = 0;
	water_stifled = OverrideOperation::stay_original;
	injured_on_impact = OverrideOperation::stay_original;
	injured_on_burning = OverrideOperation::stay_original;
	injured_on_poisoned = OverrideOperation::stay_original;

	tags = std::list<GeneTag>();

	callback_onBasicSkill = nullptr;
	callback_onBurning = nullptr;
	callback_onDead=nullptr;
	callback_onIdle = nullptr;
	callback_onImpact=nullptr;
	callback_onKill=nullptr;
	callback_onMoving=nullptr;
	callback_onPoisoned=nullptr;
	callback_onSpecialSkill=nullptr;
	callback_onHit = nullptr;
	callback_onVanish = nullptr;

	gene_num++;
}

Gene::~Gene()
{
	gene_num--;
}


void Gene::trigger_onIdle(Chara* chara) const
{
	if (callback_onIdle)
		callback_onIdle(chara);
}

void Gene::trigger_onMoving(Chara* chara) const
{
	if (callback_onMoving)
		callback_onMoving(chara);
}

void Gene::trigger_onBasicSkill(Chara* chara) const
{
	if (callback_onBasicSkill)
		callback_onBasicSkill(chara);
}

void Gene::trigger_onSpecialSkill(Chara* chara) const
{
	if (callback_onSpecialSkill)
		callback_onSpecialSkill(chara);
}

void Gene::trigger_onKill(Chara* chara) const
{
	if (callback_onKill)
		callback_onKill(chara);
}

void Gene::trigger_onDead(Chara* chara) const
{
	if (callback_onDead)
		callback_onDead(chara);
}

void Gene::trigger_onVanish(Chara* chara) const
{
	if (callback_onVanish)
		callback_onVanish(chara);
}

void Gene::trigger_onImpact(Chara* chara) const
{
	if (callback_onImpact)
		callback_onImpact(chara);
}

void Gene::trigger_onBurning(Chara* chara) const
{
	if (callback_onBurning)
		callback_onBurning(chara);
}

void Gene::trigger_onPoisoned(Chara* chara) const
{
	if (callback_onPoisoned)
		callback_onPoisoned(chara);
}

void Gene::trigger_onHit(Chara* chara) const
{
	if (callback_onHit)
		callback_onHit(chara);
}

bool Gene::operator<(Gene tar)
{
	const auto my_i = this->name.size() + static_cast<unsigned long long>(*this->name.begin());
	const auto tar_i= tar.name.size() + static_cast<unsigned long long>(*tar.name.begin());
	return my_i < tar_i;
}

int Gene::gene_num = 0;

int Gene::getGeneNum()
{
	return gene_num;
}


//integration_gene_container部分

integration_gene_container::integration_gene_container()
{
	capacity = 8;
	contents = std::list<Gene*>();
#ifdef _DEBUG
	SDL_LogWarn(SDL_LOG_CATEGORY_ERROR, u8"警告，基因容器没有设置目标");
#endif
}
integration_gene_container::integration_gene_container(Chara* _host)
{
	capacity = 8;
	if(_host==nullptr)
	{
#ifdef _DEBUG
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, u8"不可设置为integration_gene_container设置空的目标,已阻止");
#endif
		return;
	}
	host = _host;
	contents = std::list<Gene*>();
}

void integration_gene_container::setHost(Chara* chara)
{
	host = chara;
}

void integration_gene_container::addGene(Gene* g)
{
	if (contents.size() >= static_cast<unsigned long long>(capacity))
		return;
	contents.push_back(g);
	contents.sort();
}

void integration_gene_container::removeGene(Gene* g)
{
	contents.remove(g);
	g->destroy();
}

void integration_gene_container::transGeneTo(Gene* g, integration_gene_container* container)
{
	container->addGene(g);
	contents.remove(g);
}

unsigned long long integration_gene_container::getCapacity() const
{
	return capacity;
}

void integration_gene_container::setCapacity(unsigned long long num)
{
	capacity = num;
	//检查超出
	auto i = contents.begin();
	unsigned long long count = 0;
	while (true)
	{
		if(i==contents.end())break;
		count++;
		if (count > num )
		{
			(*i)->destroy();
			i = contents.erase(i);
		}else
		{
			++i;
		}
	}
}

unsigned long long integration_gene_container::getNum() const
{
	return contents.size();
}

void integration_gene_container::sort()
{
	contents.sort();
}

std::list<std::wstring> integration_gene_container::getGeneNameList()
{
	auto out = std::list<std::wstring>();
	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		out.push_back((*i)->name);
	}
	return out;
}

bool integration_gene_container::getGeneTag(GeneTag t)
{
	if (!host)return false;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		if(std::find((*i)->tags.begin(),(*i)->tags.end(),t)!=(*i)->tags.end())
		{
			return true;
		}
	}
	return false;
}

double integration_gene_container::getExtraSpeed()
{
	double out = 0;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		out += (*i)->extra_speed;
	}
	return out;
}

int integration_gene_container::getExtraHealth()
{
	int out = 0;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		out += (*i)->extra_health;
	}
	return out;
}

double integration_gene_container::getExtraHealthRecovery()
{
	double out = 0;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		out += (*i)->extra_health_recovery;
	}
	return out;
}

int integration_gene_container::getExtraStamina()
{
	int out = 0;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		out += (*i)->extra_stamina;
	}
	return out;
}

double integration_gene_container::getExtraStaminaRecovery()
{
	double out = 0;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		out += (*i)->extra_stamina_recovery;
	}
	return out;
}

OverrideOperation integration_gene_container::getWaterStifled()
{
	bool override_true = false; bool override_false = false;
	auto out = OverrideOperation::stay_original;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		//跳过默认的
		if ((*i)->water_stifled == OverrideOperation::stay_original)continue;
		if ((*i)->water_stifled == OverrideOperation::override_true)override_true = true;
		else if ((*i)->water_stifled == OverrideOperation::override_false)override_false = true;
	}

	if (override_true && override_false)
	{
		out = OverrideOperation::stay_original;
	}
	else if(override_true)
	{
		out = OverrideOperation::override_true;
	}
	else if(override_false)
	{
		out = OverrideOperation::override_false;
	}

	return out;
}

OverrideOperation integration_gene_container::getInjuredOnImpact()
{
	bool override_true = false; bool override_false = false;
	OverrideOperation out = OverrideOperation::stay_original;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		//跳过默认的
		if ((*i)->injured_on_impact == OverrideOperation::stay_original)continue;
		if ((*i)->injured_on_impact == OverrideOperation::override_true)override_true = true;
		else if ((*i)->injured_on_impact == OverrideOperation::override_false)override_false = true;
	}

	if (override_true && override_false)
	{
		out = OverrideOperation::stay_original;
	}
	else if (override_true)
	{
		out = OverrideOperation::override_true;
	}
	else if (override_false)
	{
		out = OverrideOperation::override_false;
	}

	return out;

}

OverrideOperation integration_gene_container::getInjuredOnBurning()
{
	bool override_true = false; bool override_false = false;
	OverrideOperation out = OverrideOperation::stay_original;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		//跳过默认的
		if ((*i)->injured_on_burning == OverrideOperation::stay_original)continue;
		if ((*i)->injured_on_burning == OverrideOperation::override_true)override_true = true;
		else if ((*i)->injured_on_burning == OverrideOperation::override_false)override_false = true;
	}

	if (override_true && override_false)
	{
		out = OverrideOperation::stay_original;
	}
	else if (override_true)
	{
		out = OverrideOperation::override_true;
	}
	else if (override_false)
	{
		out = OverrideOperation::override_false;
	}

	return out;

}

OverrideOperation integration_gene_container::getInjuredOnPoisoned()
{
	bool override_true = false; bool override_false = false;
	OverrideOperation out = OverrideOperation::stay_original;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		//跳过默认的
		if ((*i)->injured_on_poisoned == OverrideOperation::stay_original)continue;
		if ((*i)->injured_on_poisoned == OverrideOperation::override_true)override_true = true;
		else if ((*i)->injured_on_poisoned == OverrideOperation::override_false)override_false = true;
	}

	if (override_true && override_false)
	{
		out = OverrideOperation::stay_original;
	}
	else if (override_true)
	{
		out = OverrideOperation::override_true;
	}
	else if (override_false)
	{
		out = OverrideOperation::override_false;
	}

	return out;

}

void integration_gene_container::triggerOnIdle()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onIdle(host);
	}
}

void integration_gene_container::triggerOnMoving()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onMoving(host);
	}
}

void integration_gene_container::triggerOnBasicSkill()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onBasicSkill(host);
	}
}

void integration_gene_container::triggerOnSpecialSkill()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onSpecialSkill(host);
	}
}

void integration_gene_container::triggerOnKill()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onKill(host);
	}
}

void integration_gene_container::triggerOnDead()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onDead(host);
	}
}

void integration_gene_container::triggerOnVanish()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onVanish(host);
	}
}

void integration_gene_container::triggerOnImpact()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onImpact(host);
	}
}

void integration_gene_container::triggerOnBurning()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onBurning(host);
	}
}

void integration_gene_container::triggerOnPoisoned()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onPoisoned(host);
	}
}

void integration_gene_container::triggerOnHit()
{
	if (!host)return;

	for (auto i = contents.begin(); i != contents.end(); ++i)
	{
		(*i)->trigger_onHit(host);
	}
}
