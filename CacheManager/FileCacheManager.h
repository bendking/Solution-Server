//
// Created by Yaron Israel on 2019-01-04.
//

#ifndef SOLUTION_SERVER_FILECACHEMANAGER_H
#define SOLUTION_SERVER_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
/////////////////////////////////////////////////////////////////////
/// there is a bug, only saves the matrix and not the goal & start///
/////////////////////////////////////////////////////////////////////
using namespace std;

class FileCacheManager : public CacheManager<string, string> {
private:
    unordered_map<string, string> map;
    string fileName;
public:
    // Constructor & Destructor
    explicit FileCacheManager(string _fileName);
    ~FileCacheManager() override;

    // Cache Manager functions
    bool exists(string _problem) override;
    string getSolution(string _problem) override;
    void saveSolution(string _problem, string _solution) override;

    // File management
    void loadFromFile();
    void saveAllToFile();


    // Get line to format
    string formatLine(string line, char c1 = '\n', char c2 = '$');
    // Undo format
    string deformatLine(string line, char c1 = '$', char c2 = '\n');

};


#endif //SOLUTION_SERVER_FILECACHEMANAGER_H
