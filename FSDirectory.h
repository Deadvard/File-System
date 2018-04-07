#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FSNode.h"
#include "FSFile.h"

class FSDirectory : public FSNode
{
public:
	FSDirectory(std::string name);
	virtual ~FSDirectory();

	FSNode* at (int index) const;

	/* Add new file or dir */
	void addFile(FSFile* newNode);
    void addDirectory(FSDirectory* newNode);

    /* Remove node at index */
	void removeNode(int dirIndex);

	int getMax() const;

private:
	FSNode** nodes;
	int nrOfNodes;
	int maxNodes;

	void expand();
    void freeMemory();

};

#endif // !DIRECTORY_H



