#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "System.h"

using namespace std;
class Command
{
protected:
	
	System* sys = 0;
	vector<string> validArgs;
	vector<string> passedArgs;
	
	virtual int parseArgs() = 0;
public:
	string name = "";
	virtual int exec();
	
	void setSystem(System* sys);
	void setArgs(vector<string> args);
};

class NoCommand :public Command {
	int parseArgs() { return 0; };
public:
	NoCommand(string name);
	
	int exec();
	
};

class CommandCD: public Command {
	int parseArgs();
public:
	CommandCD();

	//int exec();
};

class CommandEXIT : public Command {
	int parseArgs();
public:
	CommandEXIT();

	int exec();
};

class CommandLS : public Command {
	int parseArgs();
public:
	CommandLS();

	//int exec();
	
};
