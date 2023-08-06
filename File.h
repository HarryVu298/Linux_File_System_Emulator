// File Class definition
#pragma once
#include <iostream>
#include <string>
// add necessary library
#include "System.h"

class File : public FileSystemObject {
  // if you need, you can add private members 
  
 public:
    // Constructor method to File
    File(const std::string& name, const std::string& owner, const std::string& group,
        std::string permissions, int numHardLinks, int sizeMB);
    // Destructor for File
    ~File();

    // Method to check whether it is a File or Directory
    bool isFile() const override;
    bool isDirectory() const override;
    // you can override / add member functions
    
};
