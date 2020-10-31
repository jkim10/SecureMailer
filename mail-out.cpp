#include <iostream>
#include <iomanip>
#include <fstream>
#include <dirent.h>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <sstream> 
using namespace std;

string left_padInt(int n){
    string x = to_string(n);
    x.insert(x.begin(),5 - x.length(), '0');
    return x;
}
string getNewFileName(string filePath){
    cout << "===========" << endl;
    int max_num = -1;
    int i;
    int numFiles = 0;
    stringstream ss;
    ss << setw(5);
    DIR* dirp = opendir(filePath.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        ss << (dp -> d_name);
        ss >> i;
        cout << ss.str() << endl;
        max_num = max(max_num,i);
        numFiles++;
    }
    stringstream res;
    if(numFiles == 2) {return "00000";}
    res << setw(5) << setfill('0') << (max_num+1);
    cout << "===========" << endl;
    return res.str();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./mail-out <receipient> \n");
        return 1;
    }
    string rec = argv[1];
    string mailbox_path = "./mail/" + rec;
    struct stat info;
    if ((stat(mailbox_path.c_str(), &info)) != 0){
        return 2;
    } else if ( info.st_mode & S_IFDIR){
        string line;
        string newFileName = getNewFileName(mailbox_path);
        string newFilePath = mailbox_path + "/" + newFileName;
        ofstream fs(newFilePath.c_str());
        while (getline(cin, line))
        {
            fs << line;
            fs << "\n";
        }
        return 0;
    } else{
        return 3;
    }
    return 4;
}