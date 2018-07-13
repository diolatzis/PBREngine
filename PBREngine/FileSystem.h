#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Types.h"


class FileSystem
{
public:
	FileSystem();
	~FileSystem();

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

