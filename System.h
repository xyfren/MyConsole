#pragma once
#include <string>
#include <vector>
using namespace std;

class System
{
	
public:
	bool isRunning;
	string path = "~";

	System();

	void exit();
};
