#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

struct FileLines {
    int size = 0;
    vector<string> lines;
    string line;
};

FileLines loadFileLines(string FileName);
string toUpperCase(string str);
string removeSpaces(string str);