#pragma once
#include <string>
#include <vector>

using namespace std;


class FileSystemComponent
{
protected:
	string name;
	short type;
public:

	FileSystemComponent() {
		type = 0;
	};
	virtual FileSystemComponent* getParent() const = 0;
	virtual string getName() const = 0;
	virtual string getPath() = 0;
	virtual short getType() const = 0;
};

class File :  public FileSystemComponent {
private:

	FileSystemComponent* parent;
public:
	File(string name) {
		this->name = name;
		this->parent = nullptr;
		this->type = 2;
	}
	FileSystemComponent* getParent() const override { return parent; }
	string getName() const override { return name; }
	string getPath() override {
		string path = "";
		FileSystemComponent* currentObject = dynamic_cast<FileSystemComponent *>(this);
		while (currentObject->getParent() != nullptr) {
			path = "\\" + currentObject->getName() + path;
			currentObject = currentObject->getParent();
		}
		return path;
	}
	
	short getType() const override { return type; }

	void setParent(FileSystemComponent* component) {
		parent = component;
	}
};


class Directory : public FileSystemComponent {
protected:

	FileSystemComponent* parent;
public:
	Directory() {
		this->name = "New Directory";
		this->parent = nullptr;
		this->type = 1;
	}

	Directory(string name) {
		this->name = name;
		this->parent = nullptr;
		this->type = 1;
	}

	vector<FileSystemComponent*> subObjects;

	FileSystemComponent* getParent() const override { return parent; }
	vector<FileSystemComponent*> getSubObjects() const { return subObjects;}
	string getName() const override { return name; }
	string getPath() override {
		string path;
		FileSystemComponent* currentObject = dynamic_cast<FileSystemComponent*>(this);
		while (currentObject->getParent() != nullptr) {
			path = "\\" + currentObject->getName() + path;
			currentObject = currentObject->getParent();
		}
		return path;
	}
	short getType() const override { return type; }

	void setParent(FileSystemComponent* component) {
		parent = component;
	}
	void addComponent(FileSystemComponent* component) {
		if (component->getType() == 1) {
			Directory* directory = dynamic_cast<Directory*>(component);
			directory->setParent(this);
		}
		else if (component->getType() == 2) {
			File* file = dynamic_cast<File*>(component);
			file->setParent(this);
		}
		subObjects.push_back(component);
	}
};


class Root : public Directory {
public:
	Root() {
		this->parent = nullptr;
		this->name = "Root";
	}

	vector<FileSystemComponent*> subObjects;

	FileSystemComponent* getParent() const override { return nullptr; }
	string getPath() override { return "\\"; }
};
