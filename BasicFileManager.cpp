#include <iostream>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <string>

using namespace std;
namespace fs = filesystem;

//Directory Navigation
void listDirectoryContents(const string& directoryPath)
{
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(directoryPath.c_str())) != nullptr)
    {
        while ((entry = readdir(dir)) != nullptr)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                cout << entry->d_name << '\n';

        }
        closedir(dir);
    }
    else
        perror("opendir");
}

//View a file
void viewFile(const string& filePath)
{
    ifstream file(filePath);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
            cout << line << endl;

        file.close();
    }
    else
        cout << "Unable to open file: " << filePath << endl;

}

// Create a directory
void createDirectory(const string& path, const string& directoryName)
{
    string fullPath = path + "\\" + directoryName;
    try
    {
        if (filesystem::create_directory(fullPath))
            cout << "Directory created successfully "<<endl;
        else
            cerr << "Failed to create directory"<< endl;
    }
    catch (const filesystem::filesystem_error& e)
    {
        cerr << "Error creating directory: " << e.what() << endl;
    }
}


// Copy a file
bool copyFile(const string& source, const string& destinationDirPath)
{
    try
    {
        fs::copy(source, destinationDirPath + "/" + fs::path(source).filename().string(), fs::copy_options::overwrite_existing);
        cout << "File copied successfully." << endl;
        return true;
    }
    catch (const fs::filesystem_error& e)
    {
        cerr << "Error occurred during copying: " << e.what() << endl;
        return false;
    }
}

// Move File
void moveFile(const string& source, const string& destinationDirPath)
{
    try
    {
        fs::rename(source, destinationDirPath + "/" + fs::path(source).filename().string());
        cout << "File moved successfully." << endl;
    }
    catch (const fs::filesystem_error& e)
    {
        cerr << "Error occurred during moving: " << e.what() << endl;
    }
}

int main() {
    cout << "Welcome!" << endl;
    string DirectoryPath;
    while (true) {
        cout << "Here are the options you can choose from:" << endl
             << "Press: " << endl
             << "1. list: List directory contents" << endl
             << "2. view: View file content" << endl
             << "3. create: Create directory" << endl
             << "4. copy: Copy file" << endl
             << "5. move: Move file" << endl
             << "6. exit: Exit the file manager" << endl;

        int command;
        cin >> command;
        cin.ignore();
        switch (command) {
            case 1:
                cout << "Enter the path of the directory you want to list its contents:" << endl;
                getline(cin, DirectoryPath);
                cout << "Contents of " << DirectoryPath << endl;
                listDirectoryContents(DirectoryPath);
                cout << endl;
                break;
            case 2:
            {
                string filePath;
                cout << "Enter the path of the file you want to view: "<<endl;
                getline(cin, filePath);
                cout << endl;
                viewFile(filePath);
                cout << endl;
                break;
            }
            case 3: {
                string newDirectoryName, path;
                cout << "Enter the path where you want to create the new directory:"<<endl;
                getline(cin, path);
                cout << "Enter the name of the new directory: ";
                getline(cin, newDirectoryName);
                createDirectory(path, newDirectoryName);
                cout << endl;
                break;
            }
            case 4: {
                string sourcePath, destinationDirPath;
                cout << "Enter the path of the file you want to copy: "<<endl;
                getline(cin, sourcePath);
                cout << "Enter the path of the directory where you want to paste it: "<<endl;
                getline(cin, destinationDirPath);
                copyFile(sourcePath, destinationDirPath);
                cout << endl;
                break;
            }
            case 5: {
                string sourcePath, destinationDirPath;
                cout << "Enter the path of the file you want to move: "<<endl;
                getline(cin, sourcePath);
                cout << "Enter the path of the directory where you want to move to: "<<endl;
                getline(cin, destinationDirPath);
                moveFile(sourcePath, destinationDirPath);
                cout << endl;
                break;
            }
            case 6: {
                cout << "Thanks for using the program! See you again!" << endl;
                cout << "Exiting ..." << endl;
                return 0;
            }
            default:
                cout << "Invalid command. Please try again." << endl;
        }
    }
}