#include "FSNode.h"

FSNode::FSNode(std::string name)
{
	this->name = name;
	this->owner = nullptr;
}

FSNode::~FSNode()
{

}

std::string FSNode::getName() const
{
	return this->name;
}

void FSNode::setName(std::string newName)
{
	this->name = newName;
}

FSNode* FSNode::getOwner() const
{
	return this->owner;
}

void FSNode::setOwner(FSNode* newOwner)
{
	this->owner = newOwner;
}
