#pragma once
#include <iostream>
#include <string>
#include <map>
#include "System.h"
#include "File.h"
// add necessary library

class Directory : public FileSystemObject {
 private:
    // The map to hold the name and the Address of the object
    std::map<std::string, FileSystemObject*> contents;

 public:
    // Construtor
    Directory(const std::string& name, const std::string& owner, const std::string& group, std::string permissions,
     int numHardLinks, int sizeMB);
     // Destructor
    ~Directory();
    // Copy Construtor
    Directory(const Directory & d);
    // Method to determine the type
    bool isFile() const override;
    // Method to determine the type
    bool isDirectory() const override;
    // Getter method
    FileSystemObject* getContents(std::string filename);

    // add necessary member methods to run ls, chmod from a directory object
    // add content 
    void addContent(const std::string& name, FileSystemObject* obj);
    // get method
    FileSystemObject* getContent(const std::string& name) const;
    // remove content method
    bool removeContent(const std::string& name);
    // update permission method
    bool updatePermission(const std::string& name, const std::string& new_permission);
    // save to file method
    void saveToFile(std::ofstream& output_file);
    // list content methods
    void listContent() const;
    // list content long method
    void listContentLong() const;
    // get total size method
    int getTotalSize() const;

    // Bonus (Rename and remove)
    bool renameObject(const std::string& old_name, const std::string& new_name);
    bool removeObject(const std::string& name);
    // find method
    FileSystemObject* find(const std::string& fileName);
    
};

