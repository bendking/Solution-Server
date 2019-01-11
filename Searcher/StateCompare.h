//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_STATECOMPARE_H
#define SOLUTION_SERVER_STATECOMPARE_H

#include "State.h"

template <class T>
class StateCompare {
public:
    bool operator() (State<T> *a, State<T> *b) {
        return a->getCost() < b->getCost();
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
