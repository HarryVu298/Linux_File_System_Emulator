#include <iostream>
#include <string>
#include "File.h"

// Implementation of constructor
File::File(const std::string& name, const std::string& owner, const std::string& group,
    std::string permissions, int numHardLinks, int sizeMB)
    : FileSystemObject(name, owner, group, permissions, numHardLinks, sizeMB) {}

// Methods to determine the type
bool File::isFile() const {
    return true;
}
// Methods to determine the type
bool File::isDirectory() const {
    return false;
}
// implement the rest of the members
// Destructor
File::~File() {
    std::cout << "The object: " << getName() << " has been released on the heap" << std::endl;
}
