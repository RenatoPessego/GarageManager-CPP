#include "Files.h"

FileLines loadFileLines(string FileName) {
    FileLines fileLines;
    
    ifstream file(FileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            fileLines.lines.push_back(line);
        }
        file.close();
    }
    
    fileLines.size = (int)fileLines.lines.size();
    return fileLines;
}

string toUpperCase(string str) {
    string result = str;
    for (char& c : result) {
        c = toupper(c);
    }
    return result;
}

string removeSpaces(string str) {
    string result;
    result.reserve(str.size());
    for (char c : str) {
        if (c != ' ') {
            result.push_back(c);
        }
    }
    return result;
}