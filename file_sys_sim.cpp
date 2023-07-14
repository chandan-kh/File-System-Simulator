#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <dirent.h>

class FileManager {
private: 
    std::string directoryPath;
                                              
public:
    void setDirectoryPath(const std::string& path) {
        directoryPath = path;
    }
    
    void createFile() {
        std::string filename;
        std::cout<<"Enter the filename: ";
        std::cin>>filename;

        std::string filepath = directoryPath + "\\" + filename;            // to pass as directory
        std::ofstream file(filepath);

        if (file) {
            std::cout<<"File created successfully.\n";
            file.close();
        } else {
            std::cout<<"Error creating file.\n";
        }
    }

    void readFile(const std::string& filename) {
        std::string filepath = directoryPath + "\\" + filename;           //// to pass as directory
        std::ifstream file(filepath);

        if (file) {
            std::cout<<"File contents:\n";

            std::string line;
            while (std::getline(file, line)) {
                std::cout<<line<<'\n';
            }

            file.close();
        } else {
            std::cout<<"Error opening file.\n";
        }
    }

    void writeFile(const std::string& filename) {
        std::string filepath = directoryPath + "\\" + filename;             // to pass as directory
        std::ofstream file(filepath, std::ios::app);                        // appending at last 

        if (file) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');       // Here, the \n acts as a delimiter.... that is the point upto which the code has to be ignored
            std::cout<<"Enter the text to write (press Enter on an empty line to finish):\n";

            std::string line;
            while (std::getline(std::cin, line) && !line.empty()) {
                file<<line<<'\n';
            }

            file.close();
            std::cout<<"File written successfully.\n";
        } else {
            std::cout<<"Error opening file.\n";
        }
    }

    void deleteFile(const std::string& filename) {
        std::string filepath = directoryPath + "\\" + filename;    // to pass as directory

        if (std::remove(filepath.c_str()) == 0) {                  // C-style string (null-terminated character array). to pass it to const char*
            std::cout<<"File deleted successfully.\n";
        } else {
            std::cout<<"Error deleting file.\n";
        }
    }

    void listFiles() {
        std::cout<<"Available files in the current directory:\n";

        DIR* directory = opendir(directoryPath.c_str());
        if (directory) {
            dirent* entry;
            while ((entry = readdir(directory)) != nullptr) {
                if (entry->d_type == DT_REG) {
                    std::cout<<entry->d_name << '\n';
                }
            }
            closedir(directory);
        } else {
            std::cout<<"Error opening directory.\n";
        }
    }
};

class DirectoryManager {
private:
    std::string directoryPath;

public:
    void setDirectoryPath(const std::string& path) {
        directoryPath = path;
    }

    void createDirectory(const std::string& directoryName) {
        std::string path = directoryPath + "\\" + directoryName;    // to pass as directory
        std::string command = "mkdir " + path;
        int result = std::system(command.c_str());

        if (result == 0) {
            std::cout<<"Directory created successfully.\n";
        } else {
            std::cout<<"Error creating directory.\n";
        }
    }

    void deleteDirectory(const std::string& directoryName) {
        std::string path = directoryPath + "\\" + directoryName;     // to pass as directory
        std::string command = "rmdir " + path;
        int result = std::system(command.c_str());

        if (result == 0) {
            std::cout<<"Directory deleted successfully.\n";
        } else {
            std::cout<<"Error deleting directory.\n";
        }
    }
};

class Menu {
private:
    FileManager fileManager;
    DirectoryManager directoryManager;

public:
    void displayMenu() {
        std::string directoryPath;
        std::cout<<"Enter the target directory path: ";
        std::cin>>directoryPath;
        
        fileManager.setDirectoryPath(directoryPath);
        directoryManager.setDirectoryPath(directoryPath);

        char choice;

        do {
            std::cout<<"\nMenu:\n";
            std::cout<<"a) Create a file\n";
            std::cout<<"b) Read a file\n";
            std::cout<<"c) Write to a file\n";
            std::cout<<"d) Delete a file\n";
            std::cout<<"e) List files\n";
            std::cout<<"f) Create Directory\n";
            std::cout<<"g) Delete Directory\n";
            std::cout<<"h) Exit the program\n";
            std::cout<<"Enter your choice: ";
            std::cin>>choice;

            switch (choice) {
                case 'a': {
                    fileManager.createFile();
                    break;
                }
                case 'b': {
                    std::string filename;
                    std::cout<<"Enter the filename to read: ";
                    std::cin>>filename;
                    fileManager.readFile(filename);
                    break;
                }
                case 'c': {
                    std::string filename;
                    std::cout<<"Enter the filename to write: ";
                    std::cin>>filename;
                    fileManager.writeFile(filename);
                    break;
                }
                case 'd': {
                    std::string filename;
                    std::cout<<"Enter the filename to delete: ";
                    std::cin>>filename;
                    fileManager.deleteFile(filename);
                    break;
                }
                case 'e': {
                    fileManager.listFiles();
                    break;
                }
                case 'f': {
                    std::string directoryName;
                    std::cout<<"Enter the directory name to create: ";
                    std::cin>>directoryName;
                    directoryManager.createDirectory(directoryName);
                    break;
                }
                case 'g': {
                    std::string directoryName;
                    std::cout<<"Enter the directory name to delete: ";
                    std::cin>>directoryName;
                    directoryManager.deleteDirectory(directoryName);
                    break;
                }
                case 'h':
                    std::cout<<"Exiting the program.\n";
                    break;
                default:
                    std::cout<<"Invalid choice. Please try again.\n";
                    break;
            }
        } while (choice != 'h');
    }
};

int main() {
    Menu menu;
    menu.displayMenu();
    return 0;
}
