#include "Gene.h"
Gene* Gene::createNew()
{
	return new Gene();
}

void Gene::destroy()
{
	delete this;
}

Gene::Gene()
{
	
}

Gene::~Gene()
{
	
}

int Gene::gene_num = 0;

int Gene::getGeneNum()
{
	return gene_num;
}
