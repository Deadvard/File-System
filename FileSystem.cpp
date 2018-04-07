#include "FileSystem.h"

FileSystem::FileSystem()
{
	fs = nullptr;
}

FileSystem::~FileSystem()
{
	delete fs;
}

void FileSystem::initializeSystem(const char data[])//här är felet
{
	int nrOfBlocks = 250;

	mMemblockDevice = MemBlockDevice(nrOfBlocks);

	for (int i = 0; i < nrOfBlocks; i++)
	{
		char temp[512];
		for (int j = 0; j < 512; j++)
		{
			temp[j] = data[i * 512 + j];
		}

		mMemblockDevice.writeBlock(i, temp);
	}
	std::string treeString = mMemblockDevice.readBlock(0).toString();
	char blocksChar = treeString.at(0);
	int blocksInt = atoi(&blocksChar);
	
	for (int i = 1; i < blocksInt; i++)
	{
		treeString += mMemblockDevice.readBlock(i).toString();
		mMemblockDevice.useBlock();
	}
	
	treeString.erase(0,1);
	
	if (treeString.at(0) == 0)
	{
		treeString = "{}";
	}

	delete fs;
	fs = new FSTree(treeString);
}

void FileSystem::writeBlock(int index, char newBlock[])
{
	mMemblockDevice.writeBlock(index, newBlock);
}

std::string FileSystem::readBlock(int index) const
{
	return mMemblockDevice.readBlock(index).toString();
}

std::string FileSystem::getCurrentFiles()
{
	return fs->currentFiles();
}

std::string FileSystem::getCurrentDir()
{
	return fs->currentDir();
}

std::string FileSystem::getCurrentDirPath()
{
	return fs->currentDirPath();
}

std::string FileSystem::getFileContent(std::string name)
{
	return mMemblockDevice.readBlock(fs->getFileBlock(name)).toString();
}

bool FileSystem::removeFile(std::string name)
{
	return fs->removeNode(name);
}

bool FileSystem::changeCurrentDir(std::string newDir)
{		
	return fs->enterDir(newDir);
}

void FileSystem::createFile(std::string name, std::string content)
{
	int blockId = fs->findFreeBlock() + 1;
	mMemblockDevice.useBlock();
	
	if (blockId != -1 && mMemblockDevice.spaceLeft() > 0)
	{
		fs->newFile(name, blockId);
		for (int i = content.length(); i < 512; i++)
		{
			content += (char)(0);
		}
		mMemblockDevice.writeBlock(blockId, content.c_str());
	}
}

void FileSystem::createDir(std::string dir)
{
	fs->newDir(dir);
}

bool FileSystem::renameFile(std::string oldName, std::string newName)
{
	return fs->renameNode(oldName, newName);
}

bool FileSystem::copy(std::string oldFile, std::string newFile)
{
	int result = fs->getFileBlock(oldFile);

	if (result != -1 && mMemblockDevice.spaceLeft() > 0)
	{
		Block* oldBlock = &mMemblockDevice.readBlock(result);
		std::string data = oldBlock->toString();
		int newBlockId = fs->findFreeBlock();
		mMemblockDevice.writeBlock(newBlockId, data);
		fs->newFile(newFile, newBlockId);
		mMemblockDevice.useBlock();
	}

	return result > 0;
}

std::string FileSystem::getImage()
{
	std::string treeString = fs->toString();

	int blocks = (treeString.size() / 512) + 1;
	
	treeString.insert(0, std::to_string(blocks));

	for (int i = 0; i < blocks; i++)
	{
		char temp[512];
		
		for (int j = 0; j < 512; j++)
		{
			if (i * 250 + j < treeString.size())
			{
				temp[i * 250 + j] = treeString.at(i * 250 + j);
			}
			else
			{
				temp[i * 250 + j] = 0;
			}			
		}
				
		mMemblockDevice.writeBlock(i, temp);
	}	
	
	std::string result = "";
	for (int i = 0; i < 250; i++)
	{
		result += mMemblockDevice.readBlock(i).toString();
	}	

	return result;
}
/* Please insert your code */
