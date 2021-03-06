#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Types.h"


class FileSystem
{
private:

	//Singleton instance
	static FileSystem *instance;

	//Constructors/Destructors
	FileSystem();
	~FileSystem();

public:
	

	//Start up and shut down functions of the subsystem
	void startUp();
	void shutDown();

	//Get the singleton instance
	static FileSystem& get();

	//Read binary file
	bool syncReadFile(const char *filePath, U8 *buffer, size_t bufferSize, size_t &bytesRead);

	//Open file and return it
	bool syncOpenFile(const char *filePath, std::ifstream &file);

	//Open file and return its contents in string
	std::string syncStrReadFile(const char *filePath);

};


#endif

