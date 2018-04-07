#include "FSTree.h"
#include <sstream>
#include <stdlib.h>

FSTree::FSTree(std::string treeString)
{
    this->treeString = treeString;
    this->index = 0;

    root = createDir("");
	root->setOwner(root);
    current = root;
}

FSTree::~FSTree()
{
    delete root;
}

int FSTree::findFreeBlock()
{
	return findFreeBlock(root);
}

bool FSTree::renameNode(std::string oldName, std::string newName)
{
	bool result = false;

	for (int i = 0; i < current->getMax() && !result; i++)
	{
		if (current->at(i)->getName() == oldName)
		{
			result = true;
			current->at(i)->setName(newName);
		}
	}

	return result;
}

std::string FSTree::currentDirPath() const
{
	std::string result = "";
	FSNode* walker = current;

	while (walker != root)
	{		
		result = "/" + walker->getName() + result;	
		walker = walker->getOwner();
	}

	return result;
}

std::string FSTree::currentDir() const
{
    return current->getName();
}

std::string FSTree::currentFiles() const
{
    std::string dirFiles = "";

    for(int i = 0; i < current->getMax(); i++)
    {
        dirFiles += current->at(i)->getName();
        dirFiles += " ";
    }

    return dirFiles;
}

bool FSTree::newFile(std::string name, int blockIndex)
{
    bool result = false;


    if(current)
    {
		result = true;
		
		for (int i = 0; i < current->getMax(); i++)
		{
			if (current->at(i)->getName() == name)
			{
				result = false;
			}
		}
		
		if (result)
		{
			current->addFile(new FSFile(name,blockIndex));
		}
    }
    return result;
}

bool FSTree::newDir(std::string name)
{
    bool result = false;
    if(current)
    {
        current->addDirectory(new FSDirectory(name));
        result = true;
    }
    return result;
}


bool FSTree::removeNode(std::string name)
{
    bool result = false;

    for(int i = 0; i < current->getMax() && !result; i++)
    {
        if(current->at(i)->getName() == name)
        {
            result = true;
            current->removeNode(i);
        }
    }

    return result;
}

bool FSTree::enterDir(std::string name)
{
    bool result = false;

	if (name.length() > 0 && name.at(0) == '/')
	{
		result = true;
		std::string tempStr = "";
		FSDirectory* temp = root;
		for (int j = 0; j < name.length(); j++)
		{			
			if(result && name.at(j) != '/')
			{
				tempStr += name.at(j);
			}
			
			if (result && tempStr.length() > 0 && (name.at(j) == '/' || j == name.length()-1))
			{			
				bool dirResult = false;
				
				for (int i = 0; i < current->getMax() && !dirResult; i++)
				{
					
					FSDirectory* testDir = dynamic_cast<FSDirectory*>(temp->at(i));

					if (testDir && testDir->getName() == tempStr)
					{
						temp = testDir;
						tempStr = "";
						dirResult = true;
					}
				}

				if (!dirResult)
				{
					result = false;
				}
			}
			
		}
		if (result)
		{
			 current = temp;
		}
	}
	else
	{
		for (int i = 0; i < current->getMax() && !result; i++)
		{
			FSDirectory* testDir = dynamic_cast<FSDirectory*>(current->at(i));

			if (testDir && testDir->getName() == name)
			{
				result = true;
				current = testDir;
			}
		}
	}
    return result;
}


bool FSTree::exitDir()
{
	bool result = false;

	FSDirectory* testDir = dynamic_cast<FSDirectory*>(current->getOwner());

	if (testDir)
	{
		result = true;
		current = testDir;
	}

	return result;
}

int FSTree::getFileBlock(std::string name) const
{
	int result = -1;

	for (int i = 0; i < current->getMax() && result == -1; i++)
	{
		FSFile* testFile = dynamic_cast<FSFile*>(current->at(i));

		if (testFile && testFile->getName() == name)
		{
			result = testFile->getIndex();
		}
	}

	return result;
}

std::string FSTree::toString()
{
    return stringDir(root);
}

/* Private */

int FSTree::findFreeBlock(FSDirectory* dir)
{
	int result = 0;

	for (int i = 0; i < dir->getMax(); i++)
	{
		FSFile* testFile = dynamic_cast<FSFile*>(dir->at(i));

		if (testFile && testFile->getIndex() > result)
		{
			result = testFile->getIndex();
		}
		else
		{
			FSDirectory* testDir = dynamic_cast<FSDirectory*>(dir->at(i));
			if (testDir)
			{
				const int testResult = findFreeBlock(testDir);
				if (testResult > result)
				{
					result = testResult;
				}
			}
		}
	}

	return result;
}

char FSTree::currentChar() const
{
    return index < treeString.size() ? this->treeString.at(index) : '}';
}
void FSTree::nextChar()
{
    index++;
}

std::string FSTree::collectName()
{
    std::string result = "";

    while(currentChar() != '{' && currentChar() != '[' && currentChar() != '}' && currentChar() != ']')
    {
        result += currentChar();
        nextChar();
    }

    return result;
}

FSDirectory* FSTree::createDir(std::string name)
{
    nextChar();
    FSDirectory* newDir = new FSDirectory(name);

    while(currentChar() != '}')
    {
        std::string newName = collectName();
        if(currentChar() == '[')
        {
            newDir->addFile(createFile(newName));
        }
        else
        {
            newDir->addDirectory(createDir(newName));
        }
    }
    nextChar();
    return newDir;
}

FSFile* FSTree::createFile(std::string name)
{
    nextChar();

    std::string blockId = collectName();
    FSFile* newFile = new FSFile(name, atoi(blockId.c_str()));

    nextChar();
    return newFile;
}

/* toString */

std::string FSTree::stringDir(FSDirectory* dir)
{
    std::string result = "{";
    std::string temp = "";

    for(int i = 0; i < dir->getMax(); i++)
    {
        FSFile* tempFile = dynamic_cast<FSFile*>(dir->at(i));

        if(tempFile)
        {
            result += tempFile->getName() + "[" + std::to_string(tempFile->getIndex()) + "]";
        }
        else
        {
            FSDirectory* tempDir = dynamic_cast<FSDirectory*>(dir->at(i));
            if(tempDir)
            {
                result += tempDir->getName() + stringDir(tempDir);
            }
        }
    }

    result += "}";
    return result;
}
