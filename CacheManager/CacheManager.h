//
// Created by Yaron Israel on 2019-01-04.
//

#ifndef SOLUTION_SERVER_CACHEMANAGER_H
#define SOLUTION_SERVER_CACHEMANAGER_H

#include "string"

using namespace std;

class CacheManager {

public:
    virtual ~CacheManager() = default;

    virtual bool exists(string _solution) = 0;
    virtual string getSolution(string _problem) = 0;
    virtual void saveSolution(string _problem, string _solution)  = 0;
};


#endif //SOLUTION_SERVER_CACHEMANAGER_H
