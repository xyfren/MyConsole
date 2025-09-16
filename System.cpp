#include "System.h"
System::System() {
	isRunning = false;
}

void System::exit() {
	isRunning = false;
	return;
}

bool System::isPath(string pathStr) {
    try {
        fs::path p(pathStr);
        return fs::exists(p);
    }
    catch (...) {
        return false;
    }
}