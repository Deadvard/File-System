#include "Shell.h"
#include <iostream>
#include <fstream>
#include "FileSystem.h"

Shell::Shell()
{
	
}

Shell::~Shell()
{

}

void Shell::run()
{
	format();
	
	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "user@DV1492";    // Change this if you want another user to be displayed
	std::string currentDir = "/";    // current directory, used for output

	bool bRun = true;

	while (bRun)
	{
		std::cout << user << ":" << currentDir + fSystem.getCurrentDir() << "$ ";
		getline(std::cin, userCommand);

		int nrOfCommands = parseCommandString(userCommand, commandArr);
		if (nrOfCommands > 0) {

			int cIndex = findCommand(commandArr[0]);
			switch (cIndex) {

			case 0: //quit
				bRun = quit();
				break;
			case 1: // format
				format();
				break;
			case 2: // ls
				ls();
				break;
			case 3: // create
				create(commandArr[1], commandArr[2]);
				break;
			case 4: // cat
				cat(commandArr[1]);
				break;
			case 5: //createImage
				createImage(commandArr[1]);
				break;
			case 6: //restoreImage
				restoreImage(commandArr[1]);
				break;
			case 7: // rm
				rm(commandArr[1]);
				break;
			case 8: // cp
				cp(commandArr[1], commandArr[2]);
				break;
			case 9: // mv
				mv(commandArr[1], commandArr[2]);
				break;
			case 10: // mkdir
				mkDir(commandArr[1]);
				break;
			case 11: // cd
				cd(commandArr[1]);
				break;
			case 12: // pwd
				pwd();
				break;
			case 13: // help
				std::cout << help() << std::endl;
				break;
			default:
				std::cout << "Unknown command: " << commandArr[0] << std::endl;
			}
		}
	}

}

void Shell::format()
{
	char temp[512 * 250];
	for (int i = 0; i < 512 * 250; i++)
	{
		temp[i] = 0;
	}

	fSystem.initializeSystem(temp);
}

void Shell::createImage(std::string &command)
{
	std::string buffer = fSystem.getImage();

	std::ofstream myFile(command, std::ios::out | std::ios::binary);
	myFile.write(buffer.c_str(), 512 * 250);

	myFile.close();
}

void Shell::restoreImage(std::string &command)
{
	char buffer[512 * 250];
	std::ifstream myFile(command, std::ios::in | std::ios::binary);
	myFile.read(buffer, 512 * 250);
	
	fSystem.initializeSystem(buffer);

	myFile.close();
}

int Shell::parseCommandString(const std::string &userCommand, std::string strArr[]) {
    std::stringstream ssin(userCommand);
    int counter = 0;
    while (ssin.good() && counter < MAXCOMMANDS) {
        ssin >> strArr[counter];
        counter++;
    }
    if (strArr[0] == "") {
        counter = 0;
    }
    return counter;
}
int Shell::findCommand(std::string &command) {
    int index = -1;
    for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
        if (command == availableCommands[i]) {
            index = i;
        }
    }
    return index;
}

bool Shell::quit() {
	std::cout << "Exiting\n";
	return false;
}

std::string Shell::help() {
    std::string helpStr;
    helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
    helpStr += "-----------------------------------------------------------------------------------\n" ;
    helpStr += "* quit:                             Quit OSD Disk Tool\n";
    helpStr += "* format;                           Formats disk\n";
    helpStr += "* ls     <path>:                    Lists contents of <path>.\n";
    helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n";
    helpStr += "* cat    <path>:                    Dumps contents of <file>.\n";
    helpStr += "* createImage  <real-file>:         Saves disk to <real-file>\n";
    helpStr += "* restoreImage <real-file>:         Reads <real-file> onto disk\n";
    helpStr += "* rm     <file>:                    Removes <file>\n";
    helpStr += "* cp     <source> <destination>:    Copy <source> to <destination>\n";
    helpStr += "* mv     <old-file> <new-file>:     Renames <old-file> to <new-file>\n";
    helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n";
    helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n";
    helpStr += "* pwd:                              Get current working directory\n";
    helpStr += "* help:                             Prints this help screen\n";
    return helpStr;
}

void Shell::create(std::string name, std::string content)
{
	fSystem.createFile(name, content);
}

void Shell::cat(std::string name)
{
	std::cout << fSystem.getFileContent(name) << std::endl;
}

void Shell::rm(std::string name)
{
	if (!fSystem.removeFile(name))
	{
		std::cout << "File not found!" << std::endl;
	}
}

void Shell::ls()
{
	std::cout << fSystem.getCurrentFiles() << std::endl;
}

void Shell::pwd()
{
	std::cout << fSystem.getCurrentDirPath() << std::endl;
}

void Shell::cd(std::string newDir)
{
	if (!fSystem.changeCurrentDir(newDir))
	{
		std::cout << "Directory not found!" << std::endl;
	}
}

void Shell::mkDir(std::string newDir)
{
	fSystem.createDir(newDir);
}

void Shell::mv(std::string oldName, std::string newName)
{
	if (!fSystem.renameFile(oldName, newName))
	{
		std::cout << "File not found!" << std::endl;
	}
}

void Shell::cp(std::string oldName, std::string newName)
{
	if (!fSystem.copy(oldName, newName))
	{
		std::cout << "File not found!" << std::endl;
	}
}

void Shell::append(std::string oldFile, std::string newFile)
{
	if (!fSystem.renameFile(oldFile, newFile))
	{
		std::cout << "File not found!" << std::endl;
	}
}

/* Insert code for your shell functions and call them from the switch-case */
