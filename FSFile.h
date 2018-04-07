#ifndef FSFILE_H
#define FSFILE_H

#include "FSNode.h"
#include <string>

class FSFile : public FSNode
{
public:
	FSFile(std::string name, int blockIndex);
	virtual ~FSFile();

	int getIndex() const;
	void setIndex(int blockIndex);

private:
	int blockIndex;
};

#endif // !FSFILE_H



