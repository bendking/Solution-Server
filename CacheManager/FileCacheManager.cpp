//
// Created by Yaron Israel on 2019-01-04.
//

#include "FileCacheManager.h"


FileCacheManager::FileCacheManager(string _fileName) {
    loadFromFile();
}

FileCacheManager::~FileCacheManager() {
    saveAllToFile();
}

//
// Cache Manager functions
//

bool FileCacheManager::exists(string _solution) {
    return map.count(_solution) > 0;
}

string FileCacheManager::getSolution(string _problem) {
    return map.at(_problem);
}

string FileCacheManager::saveSolution(string _problem, string _solution) {
    map[_problem] = _solution;
}

//
// File manipulation
//

void FileCacheManager::loadFromFile()
{

    // create file if needed
    ofstream file(fileName);
    file.close();

    // key and value
    string key, value;

    // load from fle
    ifstream infile(fileName);
    string problem, solution;

    // Check if succeeded opening file
    if (infile.good()) {
        // Load file here
        while ( getline (infile,problem) ) {
            if (!problem.empty()) {
                getline (infile,solution);
                map[problem] = solution;
            }
        }
    }

    // Don't forget to close the file!
    infile.close();
}

void FileCacheManager::saveAllToFile()
{
    ofstream file(fileName);

    // save all table to file
    for (auto const& x : map) {
        file << x.first << endl << x.second << endl;
    }

    // Closing the file
    file.close();
}

