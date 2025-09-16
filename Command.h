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
	int parseArgs() override { return 0; };
public:
	NoCommand(string name);
	
	int exec() override;
	
};

class CommandCD: public Command {
	int parseArgs() override;
public:
	CommandCD();

	//int exec() override;
};

class CommandEXIT : public Command {
	int parseArgs() override;
public:
	CommandEXIT();

	int exec() override;
};

class CommandLS : public Command {
	int parseArgs() override;
public:
	CommandLS();

	//int exec() override;
	
};
