//
// Created by Yaron Israel on 2019-01-04.
//

#include "FileCacheManager.h"


FileCacheManager::FileCacheManager(string _fileName) {
    fileName = _fileName;
    loadFromFile();
}

FileCacheManager::~FileCacheManager() {
    saveAllToFile();
}

//
// Cache Manager functions
//

bool FileCacheManager::exists(string _problem) {
    return map.count(_problem) > 0;
}

string FileCacheManager::getSolution(string _problem) {
    return map.at(_problem);
}

void FileCacheManager::saveSolution(string _problem, string _solution) {
    map[_problem] = _solution;
}

//
// File manipulation
//

void FileCacheManager::loadFromFile()
{
    // Create file (if not already created)
    ofstream file(fileName, std::fstream::app);

    // Key and value
    string key, value;

    // Load from fle
    ifstream infile(fileName);
    string problem, solution;

    // Check if succeeded opening file
    if (infile.good()) {
        // Load file here
        while (getline(infile, problem)) {
            if (!problem.empty()) {
                getline(infile,solution);

                unformatLine(problem);
                unformatLine(solution);

                map[problem] = solution;
            }
        }
    }

    // Don't forget to close the file!
    infile.close();
}

void FileCacheManager::saveAllToFile()
{
    // Open file
    ofstream file(fileName);

    // Save all table to file
    for (auto const& x : map) {
        file << formatLine(x.first) << endl << formatLine(x.second) << endl;
    }

    // Closing the file
    file.close();
}


// ch1 to ch2
string& replaceChar(string& str, char ch1, char ch2) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ch1)
            str[i] = ch2;
    }
    return str;
}

// Get line to format
string FileCacheManager::formatLine(string line){
    return replaceChar(line, '\n','$');
}

// Undo format
string FileCacheManager::unformatLine(string line){
    return replaceChar(line, '$','\n');
}
