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

using namespace std;
class FileCacheManager : public CacheManager {
private:
    unordered_map<string, string> map;
    string fileName;
public:
    // CTOR & DTOR
    explicit FileCacheManager(string _fileName);
    ~FileCacheManager() override;

    // Cache Manager functions
    bool exists(string _solution) override;
    string getSolution(string _problem) override;
    void saveSolution(string _problem, string _solution) override;

    // File management
    void loadFromFile();
    void saveAllToFile();
};


#endif //SOLUTION_SERVER_FILECACHEMANAGER_H
