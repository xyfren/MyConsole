#pragma once
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <fstream>
#include "SystemParams.h"
#include "System.h"
#include "Command.h"

using namespace std;

class CommandLine {
	
	int argc;
	vector<string> argv;
	string id;
	string startScriptFile;
	
	System* sys;
	Command* command;
	unordered_map <string, function<Command*()>> factory_command;
public:
	CommandLine(int argc,char *argv[]);

	int start();
private:
	
	int parseCommand(string& cmd);
	int createNewCommand(string& key);
	//int parseStartArgs();
	int runStartScript();
};

