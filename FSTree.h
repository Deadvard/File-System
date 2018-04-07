#ifndef FSTREE_H
#define FSTREE_H

#include<string>
#include "FSFile.h"
#include "FSDirectory.h"

class FSTree
{
public:
    FSTree(std::string treeString);
    virtual ~FSTree();

	/* Finds a free block */
	int findFreeBlock();

	/* Rename Node */
	bool renameNode(std::string oldName, std::string newName);
	
	/* The current directory */
	std::string currentDirPath() const;
	/* The current directory */
    std::string currentDir() const;
    /* All files in current directory */
    std::string currentFiles() const;

    /* New file corresponding to block with that id
    created in current dir */
    bool newFile(std::string name, int blockIndex);
    bool newDir(std::string name);

    /* Looks for file or dir in current dir and removes it
    returns true if successful */
    bool removeNode(std::string name);

    /* Searches for the directory with the name and makes it the current dir
    if not found returns false */
    bool enterDir(std::string name);
    bool exitDir();

    /* Returns the index of the block allocated for this file
    if -1 file was not found */
    int getFileBlock(std::string name) const;

    std::string toString();

private:
	/* Finds a free block */
	int findFreeBlock(FSDirectory* dir);

    //The string that creates the file tree
    std::string treeString;
    int index;

    FSDirectory* root;
    FSDirectory* current;

    //Create tree
    char currentChar() const;
    void nextChar();

    std::string collectName();

    FSDirectory* createDir(std::string name);
    FSFile* createFile(std::string name);

    std::string stringDir(FSDirectory* dir);
};

#endif // FSTREE_H
