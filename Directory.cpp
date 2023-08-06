#include <iostream>
#include <string>
#include <map>
#include "Directory.h"
// add necessary library
#include <fstream>

// Constructor for Directory
Directory::Directory(const std::string& name, const std::string& owner,
                     const std::string& group, std::string permissions, int numHardLinks, int sizeMB)
        : FileSystemObject(name, owner, group, permissions, numHardLinks, sizeMB) {}

// Destructor for Directory
Directory::~Directory() {
    for (auto& entry : contents) {
        std::cout << "The object: " << entry.second->getName() << " has been released on the heap" << std::endl;
        // delete entry.second;
    }
    
}

// Implementation of copy constructor
Directory::Directory(const Directory& d)
    : FileSystemObject(d.getName(), d.getOwner(), d.getGroup(), d.getPermissions(), d.getNumHardLinks(), d.getSizeMB()) {
    for (const auto& entry : d.contents) {
        FileSystemObject* newObj;
        if (entry.second->isDirectory()) {
            newObj = new Directory(*dynamic_cast<Directory*>(entry.second));
        } else {
            newObj = new File(*dynamic_cast<File*>(entry.second));
        }
        contents[entry.first] = newObj;
    }
}

// Method to determine the type
bool Directory::isFile() const {
        return false;
}

// Method to determine the type
bool Directory::isDirectory() const {
        return true;
}
 // add necessary member function implementation
 // Implementation of add content method 
void Directory::addContent(const std::string& name, FileSystemObject* obj) {
    contents[name] = obj;
}
// Implementation of get content method
FileSystemObject* Directory::getContent(const std::string& name) const {
    auto it = contents.find(name);
    if (it != contents.end()) {
        return it->second;
    }
    // return null pointer if does not exist
    return nullptr;
}
// Implementation of of remove content, return true if remove successfully
bool Directory::removeContent(const std::string& name) {
    auto it = contents.find(name);
    if (it != contents.end()) {
        delete it->second;
        contents.erase(it);
        return true;
    }
    return false;
}
// Implementation of update permission, return true if update successfully
bool Directory::updatePermission(const std::string& name, const std::string& new_permission) {
    // find the object to update
    auto it = contents.find(name);
    if (it != contents.end()) {
        // update permission
        it->second->setPermissions(new_permission);
        return true;
    }
    return false;
}

// Implementation of list content
void Directory::listContent() const {
    for (const auto& entry : contents) {
        std::cout << entry.first << " ";
    }
    std::cout << std::endl;
}

// Implementation of get total size of the root
int Directory::getTotalSize() const {
    int total = 0;
    for (const auto &item : contents) {
        FileSystemObject *fsObject = item.second;
        total += fsObject->getSizeMB();
    }
    return total;
}

// Implementation of list content long
void Directory::listContentLong() const {
    std::cout << "total: " << getTotalSize() << std::endl;
    for (const auto &item : contents) {
        FileSystemObject *fsObject = item.second;
        // std::string type = fsObject->isDirectory() ? "d" : "-";
        std::cout << fsObject->getPermissions() << " "
                  << fsObject->getNumHardLinks() << " "
                  << fsObject->getOwner() << " "
                  << fsObject->getGroup() << " "
                  << fsObject->getSizeMB() << " "
                  << fsObject->getName() << std::endl;
    }
}

// Implementation of rename ojbect (bonus)
/**
 * @param old_name the file to be renamed
 * @param new_name the new name of the file
 * @return true if rename successfully, false otherwise
*/
bool Directory::renameObject(const std::string& old_name, const std::string& new_name) {
    auto it = contents.find(old_name);
    if (it != contents.end()) {
        // Change the name on the map
        contents[new_name] = it->second;
        // change the name
        it->second->changeName(new_name);
        contents.erase(it);
        return true;
    }
    return false;
}

/**
 * Implementation of remove object (bonus)
 * @param name the object to be remove
 * @return true if remove successfully, false otherwise
*/
bool Directory::removeObject(const std::string& name) {
    auto it = contents.find(name);
    if (it != contents.end()) {
        contents.erase(it);
        return true;
    }
    return false;
}

/**
 * Implementation of find object
 * @return the address of the object
*/
FileSystemObject* Directory::find(const std::string& fileName) {
    // Search in the current directory
    auto it = contents.find(fileName);
    if (it != contents.end()) {
        return it->second;
    }
    
    return nullptr;
}

/**
 * Implementation of Save to File
 * @param output_file out stream
*/
void Directory::saveToFile(std::ofstream& output_file) {
    for (const auto& i : contents) {
        FileSystemObject *entry = i.second;
        // out steam the ouput
        if (entry->isDirectory()) {
            output_file << entry->getPermissions() << " " << entry->getNumHardLinks() << " "
                        << entry->getOwner() << " " << entry->getGroup() << " "
                        << entry->getSizeMB() << " " << entry->getName() << std::endl;
        } else {
            output_file << entry->getPermissions() << " " << entry->getNumHardLinks() << " "
                        << entry->getOwner() << " " << entry->getGroup() << " "
                        << entry->getSizeMB() << " " << entry->getName() << std::endl;
        }
    }
}



