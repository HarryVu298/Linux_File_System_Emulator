# Linux File System Emulator

## Description
This project emulates a simplified Linux file system in which users can interact with files and directories using familiar Linux commands like `ls`, `chmod`, `mv`, and `rm`.

## Features
- **Parse and Create FileSystem**: Initialize the virtual file system from a given text file.
- **LS Command**: List content of the current directory.
- **LS -l Command**: List content of the current directory in long format.
- **CHMOD Command**: Modify the permissions of a file or directory.
- **MV Command**: Rename a file or directory.
- **RM Command**: Remove a file or directory.
- **Save Updates**: Save changes made during the session back to a file.

## Usage
1. Ensure you have the required files (`Directory.cpp`, `File.cpp`, `main.cpp`, `System.cpp`, and `makefile`).
2. Compile the code using the provided makefile.
3. Run the application with the command:
./<executable_name> <input_filename>
Where `<executable_name>` is the name of the compiled binary and `<input_filename>` is the name of the file containing the initial state of the file system.

## Author
Harry Vu

## Revision History
- 0 trial: Submit by mistake.
- 1st: Test the code.
- 2nd: Output error changes.
... (and so on, as detailed in the code's comments)

## Notes
Ensure the input file is formatted correctly. Each line should represent a file or directory with attributes like permissions, owner, group, size, and name.
