//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_STATECOMPARE_H
#define SOLUTION_SERVER_STATECOMPARE_H

#include "State.h"

template <class T>
class StateCompare {
public:
    bool operator() (State<T> &a, State<T> &b)
    {
        return a.getCost() > b.getCost();
    }
};


#endif //SOLUTION_SERVER_STATECOMPARE_H
