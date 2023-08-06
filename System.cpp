// add necessary libraries
#include <iostream>
#include "System.h"

// add rest of the members' implementations if there is any
// Constructor for the FileSystemObject class
FileSystemObject::FileSystemObject(const std::string& name, const std::string& owner,
    const std::string& group, std::string permissions, int numHardLinks, int sizeMB)
        : name(name), owner(owner), group(group), permissions(permissions),
        numHardLinks(numHardLinks), sizeMB(sizeMB) {}
// Destructor for the FileSystemObject class
FileSystemObject::~FileSystemObject() {
    std::cout << "The object: " << getName() << " has been released on the heap" << std::endl;
}

// Implementation of Getter methods

const std::string& FileSystemObject::getName() const {
        return name;
}

const std::string& FileSystemObject::getOwner() const {
        return owner;
}

const std::string& FileSystemObject::getGroup() const {
        return group;
}

const std::string& FileSystemObject::getPermissions() const {
        return permissions;
}

int FileSystemObject::getNumHardLinks() const {
        return numHardLinks;
}

int FileSystemObject::getSizeMB() const {
        return sizeMB;
}


// Method to change permissions
void FileSystemObject::setPermissions(const std::string& new_permissions) {
    permissions = new_permissions;
}

// Method to change name
void FileSystemObject::changeName(std::string newName) {
    this->name = newName;
    
}


// Implementation of operator<<
std::ostream& operator<<(std::ostream& out, const FileSystemObject& c) {
    // out stream the details of the file
    out << "Name: " << c.getName() << std::endl
        << "Owner: " << c.getOwner() << std::endl
        << "Group: " << c.getGroup() << std::endl
        << "Permissions: " << c.getPermissions() << std::endl
        << "Num. Hard Links: " << c.getNumHardLinks() << std::endl
        << "Size (MB): " << c.getSizeMB() << std::endl;

    // out stream the type of the object
    if (c.isDirectory()) {
        out << "Type: Directory" << std::endl;
    } else if (c.isFile()) {
        out << "Type: File" << std::endl;
    } else {
        out << "Type: Unknown" << std::endl;
    }

    return out;
}
