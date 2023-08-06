#include<iostream>
#include<string>
#include "File.h"
#include "Directory.h"
// Add necessary libraries
#include <map>
#include <memory>
#include <fstream>
#include <sstream>

/**
 * Project 3: This project is to implementing the Linux User
 * Practice Environment
 * Author: Harry Vu
 * Coding Trails:
 * 0 trial: Submit by mistake
 * 1st: Test the code to see if it is working properly
 * 2nd: Change from "std::cerr" to "std::cout"
 * 3rd: Fix the cmd "q" to make it works as expected
 * 4th: Fix typo and fix cmd "q"
 * 5th: Fix typo
 * 6th: Fix the chmod to stop when the file does not exist
 * 7th: Fix the chmod by making it checks for filename before number notation
 * 8th: Fix the chmod in checking permission, it should check for index 3 instead of 2
 * 9th: Fix the chmod in checking permission, it should check the root's permission index 2
 * 10th: Fix the chmod in updating the permission, I forgot to add the "d" or "-" at the beginning
 * 11st: Fix typo
 * 12nd: Change the order of checking in "rm"
 * 13rd: Fix Typo
 * 14th: Fix the change name method, add changeName to File
 * 15th: Try to move the code to Zybook again
 * 16th: Add implementation of Operator << overloading, Copy Constructor
 * 17th: Add comments, finishing up documentation
*/

// add necessary functions to improve modularity of main function
// Function prototypes
void parseInputFile(const std::string &filename, std::shared_ptr<Directory> &root);
void commandLoop(std::shared_ptr<Directory> root);
void displayError(const std::string &cmd);
void saveUpdates(std::shared_ptr<Directory> root);


/**
 * This is the main method
*/
int main(int argc, char* argv[]) {
   
   // Test number of command line commands 
   if (argc != 2) {
        std::cout << "Application works with two command line arguments\n";
        return 1;
    }

   // Read file from command line command
   std::string filename(argv[1]);
   // Create the the root directory
   std::shared_ptr<Directory> root;
   // Parse input file into the root directory
   parseInputFile(filename, root);
   // if we can't open the filename
   if (!root) {
        std::cout << "Unable to open " << filename << std::endl;
        return 1;
    }
   // Menu loop for performing ls , ls -l , chmod, q and others(bonus)
   commandLoop(root);

   // Make sure there is no memory leak issue 
   // There is no memory leak issue here
    return 0;
}

/**
 * This method is used to parse the input from the filename
 * @param filename the name of the file
 * @param root the root directory
*/
void parseInputFile(const std::string &filename, std::shared_ptr<Directory> &root) {
    // input stream for filename
    std::ifstream infile(filename);

    // If the file can't be opened
    if (!infile.is_open()) {
        return;
    }

    // The line 
    std::string line;

    // Read the first line to create the root directory
    if (std::getline(infile, line)) {
        // is String Stream
        std::istringstream iss(line);
        std::string permissions, owner, group, name;
        int numHardLinks, sizeMB;
        // read the input
        iss >> permissions >> numHardLinks >> owner >> group >> sizeMB >> name;
        // make root directory
        root = std::make_shared<Directory>(name, owner, group, permissions, numHardLinks, sizeMB);
    }

    // Read the rest of the lines and create sub-items
    while (std::getline(infile, line)) {
        // Is String Stream
        std::istringstream iss(line);
        std::string permissions, owner, group, name;
        int numHardLinks, sizeMB;
        // Read the input
        iss >> permissions >> numHardLinks >> owner >> group >> sizeMB >> name;

        // Consider to see whether to create a Directory or File
        if (permissions[0] == 'd') {
            root->addContent(name, new Directory(name, owner, group, permissions, numHardLinks, sizeMB));
        } else {
            root->addContent(name, new File(name, owner, group, permissions, numHardLinks, sizeMB));
        }
    }
}

/**
 * This is method for the command loop
*/
void commandLoop(std::shared_ptr<Directory> root) {
    std::string cmd;
    // prompt to be printed out
    std::string prompt = "/home/" + root->getName() + "% ";

    // The loops for commands
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, cmd);
        // Different types of commands
        if (cmd == "q") {
            // Implement quit functionality and save updates
            saveUpdates(root);
            break;
        } else if (cmd == "ls") {
            // Implement list content functionality
            root->listContent();
        } else if (cmd == "ls -l") {
            // Implement list cotent long functionality
            root->listContentLong();
        } else if (cmd.find("chmod") == 0) {
            // Implement chmod functionality
            std::istringstream iss(cmd);
            // read in the input from the user
            std::string chmod_command, permission_str, filename;
            iss >> chmod_command >> permission_str >> filename;

            // If file is not found
            if (root->getContent(filename) == nullptr) {
                std::cout << "File or directory not found: " << filename << std::endl;
                continue;
            }

            // If the notation is invalid
            if (permission_str.size() != 3 || permission_str.find_first_not_of("01234567") != std::string::npos) {
                std::cout << "Wrong number notation" << std::endl;
                continue;
            }

            
            // If we don't have permission to change update the permission
            if (root->getPermissions()[2] != 'w') {
                std::cout << "The upper folder does not have permission." << std::endl;
            } else {
                // Change the permission from Octal to integers
                int permission_int = std::stoi(permission_str, nullptr, 8);
                std::string permission_new;
                // Add "d" if it is the directory, "-" if it is a file
                if (root->getContent(filename)->isDirectory()) {
                    permission_new += "d";
                } else {
                    permission_new += "-";
                }
                // use bitwise operator AND to make new permission
                for (int i = 0; i < 3; ++i) {
                    int mode = (permission_int >> (2 - i) * 3) & 0x7;
                    permission_new += mode & 0x4 ? 'r' : '-';
                    permission_new += mode & 0x2 ? 'w' : '-';
                    permission_new += mode & 0x1 ? 'x' : '-';
                }

                // Update the new Permission
                if (root->updatePermission(filename, permission_new)) {
                    std::cout << "The permission of file/folder has been updated." << std::endl;
                }
            }
        // Implemtation of "mv" command
        } else if (cmd.find("mv") == 0) {
            // Is String Stream
            std::istringstream iss(cmd);
            std::string chmod_command, old_name, new_name;
            // Take inputs
            iss >> chmod_command >> old_name >> new_name;

            // Find the the object to be renamed
            FileSystemObject* obj = root->find(old_name);
            // If there does not exist such an directory/file
            if (!obj) {
                std::cout << "File or directory has not been found: " << old_name << std::endl;

            // If we do not have the permission
            } else if (obj->getPermissions()[2] != 'w') {
                std::cout << "Permission denied." << std::endl;
            } else {
                // Rename the file
                if (root->renameObject(old_name, new_name)) {
                    std::cout << "The name of the file or directory has been changed." << std::endl;
                } else {
                    std::cout << "Error renaming the file or directory." << std::endl;
                }
            }

        // Implementation of "rm" method
        } else if (cmd.find("rm") == 0) {
            // Is String Stream
            std::istringstream iss(cmd);
            std::string chmod_command, name;
            // Take the inputs
            iss >> chmod_command >> name;

            // Find the object to be removed
            FileSystemObject* obj = root->find(name);
            // If the object does not exist
            if (!obj) {
                std::cout << "File or directory not found: " << name << std::endl;
            // If the file contains hard link, do not remove
            } else if (obj->getNumHardLinks() > 0) {
                std::cout << "Operation denied due the file has links" << std::endl;
            // If we don't have permission
            } else if (root->getPermissions()[2] != 'w') {
                std::cout << "The upper folder does not have permission." << std::endl;
            } else {
                // Remove it
                if (root->removeObject(name)) {
                    std::cout << "The object: " << name << " has been released on the heap" << std::endl;
                    std::cout << "The file has been removed successfully." << std::endl;
                } else {
                    std::cout << "Error removing the file or directory." << std::endl;
                }
            }
        } else {
            // If the cmd is an error
            displayError(cmd);
        }
    }
    
}


/**
 * This is the method to display the error
 * @param cmd the name of the cmd
*/
void displayError(const std::string &cmd) {
    std::cout << "Invalid command: " << cmd << std::endl;
}

/**
 * The method to save updates after modification
 * @param root the root directory
*/
void saveUpdates(std::shared_ptr<Directory> root) {
    // Response from the user
    std::string response;
    std::cout << "Do you want to save your updates (y/n) ";
    std::getline(std::cin, response);

    // If the answer is no
    if (response == "n" || response == "N") {
        return;
    }
    
    // If the answer is yes
    if (response == "y" || response == "Y") {
        std::cout << "Do you want to save your updates on the same file (y/n) ";
        std::getline(std::cin, response);

        std::string filename;
        if (response == "y" || response == "Y") {
            filename = root->getName();
        } else {
            std::cout << "Enter a new file name ";
            std::getline(std::cin, filename);
        }

        // Save the updates
        std::ofstream output_file(filename);
        if (output_file.is_open()) {
            root->saveToFile(output_file);
            output_file.close();
            std::cout << "Updates has been saved into " << filename << std::endl;
        } else {
            std::cout << "Failed to open file: " << filename << std::endl;
        }
    }
}


