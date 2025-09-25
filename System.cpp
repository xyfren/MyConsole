#include "System.h"
System::System() {
	isRunning = false;
}


void System::vfsInit() {
    stack<Directory*> componentStack;
    componentStack.push(&root);

    while (!componentStack.empty()) {
        Directory* currentComponent = componentStack.top();
        componentStack.pop();
        try {
            for (const auto& entry : fs::directory_iterator(fs::path(vfsFile + currentComponent->getPath()))) {
                if (entry.is_directory()) {
                    Directory* directory = new Directory(entry.path().filename().string());
                    currentComponent->addComponent(directory);
                    componentStack.push(directory);
                }
                else {
                    File* file = new File(entry.path().filename().string());
                    currentComponent->addComponent(file);
                }
            }
        }
        catch (const fs::filesystem_error& ex) {
            std::cout << "Ошибка доступа к " << fs::path(vfsFile + currentComponent->getPath()) << ": " << ex.what() << std::endl;
        }
    }
}

void System::exit() {
	isRunning = false;
	return;
}

bool System::isRealPath(string pathStr) {
    try {
        fs::path p(pathStr);
        return fs::exists(p);
    }
    catch (...) {
        return false;
    }
}
bool System::isVirtualPath(string pathStr) {
    return true;
}

void System::buildTree(FileSystemComponent * startComponent, int deep, bool lastChild, string prefix) {
    string connector;
    string new_prefix;
    string type;
    if (deep == 0){
        connector = "";
        type = "";
        new_prefix = prefix;
    }
    else {
        connector = "|--";
        if (startComponent->getType() == 1)
            type = " [D]";
        else
            type = " [F]";
        new_prefix = prefix + (lastChild ? "   " : "|  ");
    }
    cout << prefix << connector << startComponent->getName() << type << endl;


    if (startComponent->getType() == 1) {
        Directory* directoryComponent = dynamic_cast<Directory*>(startComponent);
        vector<FileSystemComponent*> subObjects = directoryComponent->getSubObjects();
        size_t count = subObjects.size();

        for (size_t i = 0; i < count; i++) {
            bool islastChild = (i == count - 1);
            buildTree(subObjects[i], deep + 1,islastChild, new_prefix);
        }
    }
}
