//
// Created by Yaron Israel on 2019-01-04.
//

#include "FileCacheManager.h"



// C_tor D_tor
FileCacheManager::FileCacheManager(string _fileName) {
    loadFromFile();
}
FileCacheManager::~FileCacheManager() {
    saveAllToFile();
}

// Cache Manager functions
bool FileCacheManager::isExist(string _solution) {
    if ( map.find(_solution) == map.end() ) {
        // not found
        return false;
    } else {
        // found
        return true;
    }

}

string FileCacheManager::getSolution(string _problem) {
    return map.at(_problem);
}

string FileCacheManager::saveSolution(string _problem, string _solution) {
    map[_problem] = _solution;
}

// files
void FileCacheManager::loadFromFile() {

    // create file if needed
    ofstream file(fileName);
    file.close();

    // key and value
    string key, value;

    //load from fle
    ifstream infile(fileName);
    string problem, solution;

    if (infile.good()) {


        while (! file.eof() ) {
          //  getline (file,problem);
        }

        while (infile >> key >> value)
            map[key] = value;
    }
    infile.close();
}
void FileCacheManager::saveAllToFile() {
    ofstream file(fileName);

    // save all table to file
    for (auto const& x : map) {
        file << x.first << endl << x.second << endl;
    }

    file.close();
}

