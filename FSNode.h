#ifndef FSNODE_H
#define FSNODE_H

#include <string>

class FSNode
{
public:
	FSNode(std::string name);
	virtual ~FSNode();

	std::string getName() const;
	void setName(std::string newName);

	FSNode* getOwner() const;
	void setOwner(FSNode* newOwner);

private:
	std::string name;
	FSNode* owner;
};

#endif // !FSNODE_H
