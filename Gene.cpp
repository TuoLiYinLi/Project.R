#include "Gene.h"
#include"Defined.h"

Gene* Gene::createNew() {
	Gene* g = new Gene();
#ifdef _DEBUG
	if (g == nullptr) {
		std::cout << "\t\tERROR::Gene::createNew()ÉêÇëÄÚ´æÊ§°Ü£¬ÖµÎªnullptr\n";

	}
#endif // _DEBUG
	return g;
}
void Gene::destroy() {
	delete this;
}

int Gene::currentGeneNum = 0;

int Gene::getCurrentNum() {
	return currentGeneNum;
}
Gene::Gene() {
#ifdef GENE_DEBUG
	std::cout << "\tGene::Gene()" << std::endl;
#endif // GENE_DEBUG

	currentGeneNum++;

	name = "new Gene";
	form = Form();
	triggerOnBasicSkill = false;
	triggerOnSpecialSkill = false;
	triggerOnMove = false;
	triggerOnBreed = false;
	triggerOnDeath = false;
	triggerOnAttacked = false;
	triggerOnKilling = false;
}

Gene::~Gene() {
#ifdef GENE_DEBUG
	std::cout << "\tGene::~Gene()" << std::endl;
#endif // GENE_DEBUG

	currentGeneNum--;
}