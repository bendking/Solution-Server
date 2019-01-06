//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_SEARCHABLE_H
#define SOLUTION_SERVER_SEARCHABLE_H

#include "State.h"
#include <set>

template <class T>
class Searchable {

public:
    // D_tor
    virtual ~Searchable() = default;

    // Functions of interface
    virtual State<T>* getInitialState() = 0;
    virtual bool isGoal(State<T>*) = 0;
    virtual std::set<State<T>*> getAllPossibleStates(State<T>*) = 0;
};


#endif //SOLUTION_SERVER_SEARCHABLE_H
