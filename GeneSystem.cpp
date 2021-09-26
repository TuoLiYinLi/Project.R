#include "GeneSystem.h"
#include "Defined.h"
/*
void GeneSystem::addNewGene(GeneContainer* gc,int index) {
#ifdef GENE_SYSTEM_DEBUG
	if(index>gc->geneList->size())
	std::cout << "GeneSystem::addNewGene(GeneContainer* gc,int index)\n\tERROR:index超出geneList范围" << std::endl;
#endif // GENE_SYSTEM_DEBUG
	Gene* gene = new Gene();
	auto glit= gc->geneList->begin();
	std::advance(glit, index);
	gc->geneList->insert(glit, gene);
	GeneContainer::geneNum++;
}

GeneContainer*  GeneSystem::getNewGeneContainer() {
#ifdef GENE_SYSTEM_DEBUG
	std::cout << "GeneSystem::getGeneContainer()" << std::endl;
#endif // GENE_SYSTEM_DEBUG
	return new GeneContainer();
}
*/

GeneSystem* GeneSystem::instance = nullptr;

GeneSystem::GeneSystem() {
#ifdef GENE_SYSTEM_DEBUG
	std::cout << "GeneSystem::GeneSystem()" << std::endl;
#endif // GENE_SYSTEM_DEBUG
}

GeneSystem::~GeneSystem() {
#ifdef GENE_SYSTEM_DEBUG
	std::cout << "GeneSystem::~GeneSystem()" << std::endl;
	reportMemory();
#endif // GENE_SYSTEM_DEBUG
}

GeneSystem* GeneSystem::getInstance() {
#ifdef GENE_SYSTEM_DEBUG
	std::cout << "GeneSystem::getInstance()" << std::endl;
#endif // GENE_SYSTEM_DEBUG
	if (instance == nullptr) {
		instance = new GeneSystem();
	}
	return instance;
}

void GeneSystem::destroyInstance() {
#ifdef GENE_SYSTEM_DEBUG
	std::cout << "GeneSystem::destroyInstance()" << std::endl;
#endif // GENE_SYSTEM_DEBUG
	if(instance!=nullptr) delete instance;
	instance = nullptr;
}

void GeneSystem::reportMemory() {
	std::cout << "GeneSystem::reportMemory()\n";
	std::cout <<"\t\t现在有" << Gene::getCurrentNum() << "个Gene占用内存" << std::endl;
}