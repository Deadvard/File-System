#ifndef SHELL_H
#define SHELL_H

#include <sstream>
#include "FileSystem.h"

class Shell
{
public:
	Shell();
	virtual ~Shell();

	void run();

private:
	const static int MAXCOMMANDS = 8;
	const static int NUMAVAILABLECOMMANDS = 15;

	FileSystem fSystem;

	std::string availableCommands[NUMAVAILABLECOMMANDS] = {
		"quit","format","ls","create","cat","createImage","restoreImage",
		"rm","cp","mv","mkdir","cd","pwd","help"
	};
	void format();
	void createImage(std::string &command);
	void restoreImage(std::string &command);
	
	/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
	int parseCommandString(const std::string &userCommand, std::string strArr[]);
	int findCommand(std::string &command);
	bool quit();
	std::string help();
	
	void create(std::string name, std::string content);
	void cat(std::string name);
	void rm(std::string name);
	void ls();
	void pwd();
	void cd(std::string newDir);
	void mkDir(std::string newDir);
	void mv(std::string oldName, std::string newName);
	void append(std::string oldName, std::string newName);
	void cp(std::string oldFile, std::string newFile);
};

#endif // !SHELL_H

