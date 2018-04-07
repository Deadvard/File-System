#include "FSFile.h"


FSFile::FSFile(std::string name, int blockIndex)
	: FSNode(name)
{
	this->blockIndex = blockIndex;
}


FSFile::~FSFile()
{

}

int FSFile::getIndex() const
{
	return this->blockIndex;
}

void FSFile::setIndex(int blockIndex)
{
    this->blockIndex = blockIndex;
}
