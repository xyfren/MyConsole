#include "System.h"
System::System() {
	isRunning = false;
}

void System::exit() {
	isRunning = false;
	return;
}