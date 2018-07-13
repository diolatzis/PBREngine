#include "FileSystem.h"



FileSystem::FileSystem()
{
	//Do nothing
}


FileSystem::~FileSystem()
{
	//Do nothing
}

void FileSystem::startUp()
{

}

void FileSystem::shutDown()
{
}


FileSystem & FileSystem::get()
{
	static FileSystem* instance = NULL;
	if (instance == NULL)
	{
		instance = new FileSystem();
	}
	_ASSERT(instance);
	return *instance;
}

bool FileSystem::syncReadFile(const char * filePath, U8 * buffer, size_t bufferSize, size_t & bytesRead)
{
	FILE *handle = fopen(filePath, "rb");
	
	if (handle)
	{
		size_t bytes = fread(buffer, 1, bufferSize, handle);

		int error = ferror(handle);
		fclose(handle);

		if (error == 0)
		{
			bytesRead = bytes;
			return true;
		}
	}

	bytesRead = 0;
	return false;
}

bool FileSystem::syncOpenFile(const char *filePath, std::ifstream &file)
{
	file.open(filePath);

	if(!file.is_open())
		return false;

	return true;
}

std::string FileSystem::syncStrReadFile(const char * filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";

	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}


