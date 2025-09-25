#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "FileSystemComponent.h"
#include <stack>
namespace fs = std::filesystem;

using namespace std;

class System
{
	
public:
	bool isRunning;
	string vfsFile;

	string path = "\\";
	
	Root root;

	System();

	void vfsInit();

	void buildTree(FileSystemComponent* startComponent, int deep = 0,bool lastChild = true, string prefix = "");

	bool isRealPath(string pathStr);
	bool isVirtualPath(string pathStr);
	void exit();
};
