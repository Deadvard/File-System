#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "MemBlockDevice.h"
#include "FSTree.h"

class FileSystem
{
private:
    MemBlockDevice mMemblockDevice;
    // Here you can add your own data structures
    FSTree* fs;

public:
    FileSystem();
    ~FileSystem();

	void initializeSystem(const char data[]);
	void writeBlock(int index, char newBlock[]);
	std::string readBlock(int index) const;
	std::string getCurrentFiles();
	std::string getCurrentDir();
	std::string getCurrentDirPath();
	std::string getFileContent(std::string name);
	bool removeFile(std::string name);
	bool changeCurrentDir(std::string newDir);
	void createFile(std::string name, std::string content);
	void createDir(std::string dir);
	bool renameFile(std::string oldName, std::string newName);
	bool copy(std::string oldFile, std::string newFile);
	std::string getImage();

};

#endif // FILESYSTEM_H
