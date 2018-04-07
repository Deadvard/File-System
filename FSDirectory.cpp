#include "FSDirectory.h"

FSDirectory::FSDirectory(std::string name)
	: FSNode(name)
{
    this->nrOfNodes = 0;
    this->maxNodes = 3;
	nodes = new FSNode*[maxNodes];
}

FSDirectory::~FSDirectory()
{
    this->freeMemory();
}

FSNode* FSDirectory::at(int index) const
{
    return this->nodes[index];
}

void FSDirectory::addFile(FSFile* newNode)
{
    if(nrOfNodes >= maxNodes)
    {
		expand();
    }

    nodes[nrOfNodes] = newNode;
    nodes[nrOfNodes]->setOwner(this);

    nrOfNodes++;
}

void FSDirectory::addDirectory(FSDirectory* newNode)
{
    if(nrOfNodes >= maxNodes)
    {
        expand();
    }

    nodes[nrOfNodes] = newNode;
    nodes[nrOfNodes]->setOwner(this);

    nrOfNodes++;
}

void FSDirectory::removeNode(int dirIndex)
{
    if(dirIndex < nrOfNodes)
    {
		delete nodes[dirIndex];

        for(int i = dirIndex; i < nrOfNodes-1; i++)
        {
            nodes[i] = nodes[i+1];
        }

        nrOfNodes--;
    }
}

int FSDirectory::getMax() const
{
    return nrOfNodes;
}

/* Private */

void FSDirectory::expand()
{
    maxNodes += 3;
    FSNode** temp = new FSNode*[maxNodes];

    for(int i = 0; i < nrOfNodes; i++)
    {
        temp[i] = nodes[i];
        temp[i]->setOwner(this);
    }

    delete[] nodes;
    nodes = temp;
}

void FSDirectory::freeMemory()
{
    for(int i = 0; i < nrOfNodes; i++)
    {
		delete nodes[i];
    }

    delete[] nodes;
    nodes = nullptr;
}

