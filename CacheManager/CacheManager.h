//
// Created by Yaron Israel on 2019-01-04.
//

#ifndef SOLUTION_SERVER_CACHEMANAGER_H
#define SOLUTION_SERVER_CACHEMANAGER_H

#include "string"

using namespace std;

template<class key, class value>
class CacheManager {
public:
    virtual ~CacheManager() = default;
    virtual bool exists(key _problem) = 0;
    virtual value getSolution(key _problem) = 0;
    virtual void saveSolution(key _problem, value _solution) = 0;
};


#endif //SOLUTION_SERVER_CACHEMANAGER_H
