#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

void listFiles();
void createDirectory();
void changeDirectory();
void mainMenu();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    do {
        cout << "[1] List Files\n";
        cout << "[2] Create Directory\n";
        cout << "[3] Change Directory\n";
        cout << "[4] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                createDirectory();
                break;
            case 3:
                changeDirectory();
                break;
            case 4:
                cout << "Exiting\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

void listFiles() {
    int subChoice;
    cout << "[1] List All Files\n";
    cout << "[2] List Files by Extension\n";
    cout << "[3] List Files by Pattern\n";
    cout << "Enter your choice: ";
    cin >> subChoice;
    cin.ignore();

    if (subChoice == 1) {
        cout << "Files in \"" << fs::current_path() << "\":\n";
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            cout << entry.path().filename().string() << "\n";
        }
    } else if (subChoice == 2) {
        string extension;
        cout << "Enter file extension: ";
        getline(cin, extension);
        cout << "Files with extension " << extension << ":\n";
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (entry.path().extension() == extension) {
                cout << entry.path().filename().string() << "\n";
            }
        }
    } else if (subChoice == 3) {
        string pattern;
        cout << "Enter pattern: ";
        getline(cin, pattern);
        cout << "Files matching pattern " << pattern << ":\n";
        
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            string filename = entry.path().filename().string();
            if (pattern.find('*') != string::npos) {
                string prefix = pattern.substr(0, pattern.find('*'));
                if (filename.find(prefix) == 0) {
                    cout << filename << "\n";
                }
            }
        }
    } else {
        cout << "Invalid choice.\n";
    }
}

void createDirectory() {
    string dirName;
    cout << "Enter directory name: ";
    getline(cin, dirName);
    
    if (fs::create_directory(dirName)) {
        cout << "Directory '" << dirName << "' created successfully.\n";
    } else {
        cout << "Failed to create directory or directory already exists.\n";
    }
}

void changeDirectory() {
    string dirName;
    cout << "Enter directory name: ";
    getline(cin, dirName);
    
   
        fs::current_path(dirName);
        cout << "Changed to directory: " << fs::current_path() << "\n";
    }
}