// FileSystemObject Class definition

#pragma once
#include <iostream>
#include <string>

// This class represents a generic file system object with common attributes.
class FileSystemObject {
 protected:
    std::string name;
    std::string owner;
    std::string group;
    std::string permissions;  // Unix-style permissions, e.g. rwxr--rw-
    int numHardLinks;
    int sizeMB;
    
 public:
    // Constructor for the FileSystemObject class
    FileSystemObject(const std::string& name, const std::string& owner,
        const std::string& group, std::string permissions, int numHardLinks, int sizeMB);
    // Destructor for the FileSystemObject class
    ~FileSystemObject();
    // Getter methods for the class attributes
    const std::string& getName() const;
    const std::string& getOwner() const;
    const std::string& getGroup() const;
    const std::string& getPermissions() const;
    int getNumHardLinks() const;
    int getSizeMB() const;

    // Method to change the name of the file system object
    void changeName(std::string newName);
    
    // Virtual methods to be implemented in derived classes to check if the object is a file or directory
    virtual bool isFile() const = 0;   // 0 means it will be implemented in the derivated class
    virtual bool isDirectory() const = 0;  // it will be implemented in the derivated class
    // you can add more members 
    void setPermissions(const std::string& new_permissions);
   
};
// Method to set new permissions for the file system object
std::ostream& operator<<(std::ostream& out, const FileSystemObject & c);
