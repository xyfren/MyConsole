#pragma once
#include "CommandLine.h"

CommandLine::CommandLine(int argc,char *argv[]) {
    // ��������� ����
    string username = getUserName();
    string compname = getCompName();
    this->id = username + "@" + compname;
    const char* title = id.c_str();
    wchar_t* wtitle = new wchar_t[strlen(title) + 1];
    mbstowcs_s(0, wtitle, strlen(title) + 1, title, _TRUNCATE);
    SetConsoleTitle(wtitle);

    this->argc = argc;
    for (int i = 0; i < argc; ++i) {
        this->argv.push_back(argv[i]);
    }

    command = nullptr;
    factory_command["cd"] = []() { return new CommandCD(); };
    factory_command["ls"] = []() { return new CommandLS(); };
    factory_command["exit"] = []() { return new CommandEXIT(); };
    sys = new System();
}

int CommandLine::start() {
    int res;
    res = parseStartArgs();
    if (res < 0) {
        if (res == -1)
            cerr << "�������� ��������� ���������� ������";
        else if (res == -2)
            cerr << "������� �������� �������� ���������";
        else if (res == -3)
            cerr << "��������� �������� ���������";
        else if (res == -4)
            cerr << "�� ������ ������������ �������� -vfs";
        return 1;
    }
    
    sys->isRunning = true;
    

    //cout << "VFS:" << sys->vfsFile << endl;
    if (startScriptFile != "") {
        res = runStartScript();
        if (res < 0) {
            cerr << "������ �� ����� ���������� ���������� �������";
            //return 1;
            cerr << endl;
        }
    }
    
    string cmd;
    while (sys->isRunning) {
        cout << Color::CYAN << id << Color::RESET << ":" << sys->path << "$ ";
        getline(cin, cmd);
        int parserRes = parseCommand(cmd);
        if (parserRes == -1){
            cout << "������� " << command->name << " �� �������." << endl;
        }
        
        int res = command->exec();
        if (res == -2) {
            cout << "�������� ������������ ���������. ������� " << command->name << " -h ��� �������" << endl;
        }
        else if (res == -3) {
            cout << "������� " << command->name << " �� ��������� ����������" << endl;
        }
    }
    return 0;
}

int CommandLine::parseCommand(string& cmd) {
    istringstream ss(cmd);
    vector<string> args;
    string token;
    string bigArg;
    int i = 0;
    while (ss >> token) {
        if (i == 0) {
            int createRes = createNewCommand(token);
            if (createRes < 0) {
                return createRes;
            }
        }
        else {
            if (token.front() == '\"') {
                bigArg = token;
                while (ss >> token) {
                    if (token.back() == '\"') {
                        bigArg.push_back(' ');
                        bigArg.append(token);
                        break;
                    }
                    else {
                        bigArg.push_back(' ');
                        bigArg.append(token);
                    }
                }
                bigArg.erase(bigArg.begin());
                bigArg.erase(bigArg.end()-1);
                args.push_back(bigArg);
            }
            else {
                args.push_back(token);
            }
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

int CommandLine::parseStartArgs() {
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == "-vfs") {
            if (sys->vfsFile != "") {
                return -3;
            }
            i++;
            if (i < argc and sys->isPath(argv[i])) {
                sys->vfsFile = argv[i];
            }
            else {
                return -2;
            }
        }
        else if (argv[i] == "-ss") {
            if (startScriptFile != "") {
                return -3;
            }
            i++;
            if (i < argc and sys->isPath(argv[i])) {
                startScriptFile = argv[i];
            }
            else {
                return -2;
            }
        }
        else {
            return -1;
        }
    }
    if (sys->vfsFile == "") {
        return -4;
        //sys->vfsFile = "C:\\Users\\mikha\\source\\repos\\MyConsole\\root";
    }
    return 0;
}

int CommandLine::runStartScript() {
    ifstream file(startScriptFile, ios::in);
    if (!file) {
        return -1;
    }
    string cmd;
    while (sys->isRunning and getline(file, cmd)) {
        cout << Color::CYAN << id << Color::RESET << ":" << sys->path << "$ " << cmd << endl;
        int parserRes = parseCommand(cmd);
        if (parserRes == -1) {
            cout << "������� " << command->name << " �� �������." << endl;
            return -1;
        }

        int res = command->exec();
        if (res == -2) {
            cout << "�������� ������������ ���������. ������� " << command->name << " -h ��� �������" << endl;
            return -1;
        }
        else if (res == -3) {
            cout << "������� " << command->name << " �� ��������� ����������" << endl;
            return -1;
        }
    }
    file.close();
    return 0;
}