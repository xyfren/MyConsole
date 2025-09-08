#pragma once
#include "CommandLine.h"


CommandLine::CommandLine(string username,string compname) {
    id = username + "@" + compname;
    command = nullptr;
    
    factory_command["cd"] = []() { return new CommandCD(); };
    factory_command["ls"] = []() { return new CommandLS(); };
    factory_command["exit"] = []() { return new CommandEXIT(); };
    sys = new System();
}

int CommandLine::start() {
    string cmd;
    sys->isRunning = true;
    while (sys->isRunning) {
        cout << Color::CYAN << id << Color::RESET << ":" << sys->path << "$ ";
        getline(cin, cmd);
        int parserRes = parseCommand(cmd);
        if (parserRes == -1){
            cout << "Команда " << command->name << " не найдена." << endl;
        }
        
        int res = command->exec();
        if (res == -2) {
            cout << "Переданы недопустимые аргументы. Введите " << command->name << " -h для справки" << endl;
        }
        else if (res == -3) {
            cout << "Команда " << command->name << " не принимает аргументов" << endl;
        }
    }
    return 0;
}

int CommandLine::parseCommand(string& cmd) {
    istringstream ss(cmd);
    vector<string> args;
    string token;
    int i = 0;
    while (ss >> token) {
        if (i == 0) {
            int createRes = createNewCommand(token);
            if (createRes < 0) {
                return createRes;
            }
        }
        else {
            args.push_back(token);
        }
        i++;
    }
    command->setArgs(args);
    command->setSystem(sys);

    return 0;
}

int CommandLine::createNewCommand(string& key) {
    auto it = factory_command.find(key);
    if (it != factory_command.end()) {
        command = it->second();
        return 0;
    }
    command = new NoCommand(key);
    return -1;
}

