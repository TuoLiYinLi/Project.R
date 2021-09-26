#include "CharaSystem.h"
#include "Defined.h"
#include "CharaSlime.h"

CharaSystem* CharaSystem::instance = nullptr;

CharaSystem* CharaSystem::getInstance() {
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "CharaSystem::getInstance()\n";
#endif // CHARA_SYSTEM_DEBUG
	if (instance==nullptr) {
		instance = new CharaSystem();
	}
	return instance;
}

void CharaSystem::destroyInstance() {
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "CharaSystem::destroyInstance()\n";
#endif // CHARA_SYSTEM_DEBUG
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

CharaSystem::CharaSystem() {
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "CharaSystem::CharaSystem()\n";
#endif // CHARA_SYSTEM_DEBUG
	charaList = new std::list<Chara*>();
}

CharaSystem::~CharaSystem() {
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "CharaSystem::~CharaSystem()\n";
	int charaCount = 0;
#endif // CHARA_SYSTEM_DEBUG
	reportMemory();
	for (auto i = charaList->begin(); i != charaList->end(); i++)
	{
		if (*i != nullptr) {
			(*i)->destroy();
			(*i) = nullptr;
#ifdef CHARA_SYSTEM_DEBUG
			charaCount++;
#endif // CHARA_SYSTEM_DEBUG
		}
	}
	delete charaList;
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "\t\t销毁了charaList中"<< charaCount<<"个Chara\n";
#endif // CHARA_SYSTEM_DEBUG
}

/*
void CharaSystem::addDefaultSlime() {
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "CharaSystem::addDefaultSlime()\n";
#endif // CHARA_SYSTEM_DEBUG
	charaList->push_back(CharaSlime::createNew());
	reportMemory();
}
Chara* CharaSystem::addChara(Chara* chara)
{
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "CharaSystem::addChara(Chara* chara)\n";
#endif // CHARA_SYSTEM_DEBUG
	if (chara != nullptr && std::find(charaList->begin(), charaList->end(), chara) == charaList->end()) 
	{
		charaList->push_back(chara);
		reportMemory();
	}
	return chara;
}
*/

void CharaSystem::removeChara(Chara* chara) {
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "CharaSystem::removeChara(Chara* chara)\n";
#endif // CHARA_SYSTEM_DEBUG
	charaList->remove(chara);
	chara->destroy();
	reportMemory();
}

void CharaSystem::removeChara(int index) {
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "CharaSystem::removeChara(int index)\n";
#endif // CHARA_SYSTEM_DEBUG
	auto chara = charaAt(index);
	removeChara(chara);
}

std::list<Chara*>::iterator CharaSystem::removeChara(std::list<Chara*>::iterator it)
{
	(*it)->destroy();
	auto new_it= charaList->erase(it);
	reportMemory();
	return new_it;
}

Chara* CharaSystem::charaAt(int index) {
#ifdef CHARA_SYSTEM_DEBUG
	if(index>=charaList->size())
	std::cout << "CharaSystem::charaAt(int index)\n\t\tERROR index超出charaList范围";
#endif // CHARA_SYSTEM_DEBUG
	auto clit = charaList->begin();
	std::advance(clit, index);
	return (*clit);
}

void CharaSystem::reportMemory() {
#ifdef CHARA_SYSTEM_DEBUG
	std::cout << "CharaSystem::reportMemory()\n";
	std::cout << "\t\t现在有"<<charaList->size()<<"个Chara占用内存\n";
#endif // CHARA_SYSTEM_DEBUG
}

bool CharaSystem::ifSubmersed(Chara* chara)
{
	return false;
}

bool CharaSystem::ifFalling(Chara* chara)
{
	if (chara->form.beatback==0 && chara->movingX == 0 && chara->movingY==0) {
		
	}
	return false;
}
