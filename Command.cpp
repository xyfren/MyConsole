#include "Command.h"

void Command::setSystem(System* sys) {
	this->sys = sys;
}

void Command::setArgs(vector<string> args) {
	this->passedArgs = args;
}

int Command::exec() {
	int res = parseArgs();
	if (res < 0) {
		return res;
	}
	cout << "Команда " << name << endl;
	if (!passedArgs.empty()) {
		cout << "args: " << endl;
		for (string& str : passedArgs) {
			cout << str << " ";
		}
		cout << '\n';
	}
	else {
		cout << "Аргументы не переданы" << endl;
	}
	return 0;
}

NoCommand::NoCommand(string name) {
	this->name = name;
}

int NoCommand::exec() {
	return -100;
}
// cd
CommandCD::CommandCD() {
	this->name = "cd";
	validArgs = {"-h","-a","WAY"};
}


int CommandCD::parseArgs() {
	for (string& arg : passedArgs) {
		if (find(validArgs.begin(), validArgs.end(), arg) == validArgs.end()) {
			return -2;
		}
	}
	return 0;
}

// exit
CommandEXIT::CommandEXIT() {
	this->name = "exit";
}

int CommandEXIT::exec() {
	int res = parseArgs();
	if (res < 0) {
		return res;
	}
	sys->exit();
	return 0;
}
int CommandEXIT::parseArgs() {
	if (!passedArgs.empty()) {
		return -3;
	}
	return 0;
}

// ls
CommandLS::CommandLS() {
	this->name = "ls";
	validArgs = {"-h","-a"};
}

int CommandLS::parseArgs() {
	for (string& arg : passedArgs) {
		if (find(validArgs.begin(), validArgs.end(), arg) == validArgs.end()) {
			return -2;
		}
	}
	return 0;
}