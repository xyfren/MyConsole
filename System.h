#pragma once
#include <string>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

class System
{
	
public:
	bool isRunning;
	string vfsFile;

	string path = "~";
	System();


	bool isPath(string pathStr);
	void exit();
};
