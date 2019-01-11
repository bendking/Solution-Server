//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_STATECOMPARE_H
#define SOLUTION_SERVER_STATECOMPARE_H

#include "State.h"

template <class T>
class StateCompare {
public:
    // Returns whether left < right
    bool operator() (State<T>* left, State<T>* right) {
        return left->getCost() < right->getCost();
    }
};

template <class T>
struct StatePointerCompare
{
    State<T>* _search;
    explicit StatePointerCompare(State<T>* search) : _search(search) { }

    bool operator()(State<T>* ptr) {
        return *ptr == *_search;
    }

};

#endif //SOLUTION_SERVER_STATECOMPARE_H
