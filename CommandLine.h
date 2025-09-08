#pragma once
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <functional>
#include "SystemParams.h"
#include "System.h"
#include "Command.h"

using namespace std;

class CommandLine {
	
	string id;
	System* sys;
	Command* command;
	unordered_map <string, function<Command*()>> factory_command;
public:
	CommandLine(string username, string compname);

	int start();
private:
	
	int parseCommand(string& cmd);
	int createNewCommand(string& key);
};

