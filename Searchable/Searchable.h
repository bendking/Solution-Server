//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_SEARCHABLE_H
#define SOLUTION_SERVER_SEARCHABLE_H

#include "../Searcher/State.h"
#include <set>

template <class T>
class Searchable {
public:
    virtual ~Searchable() = default;
    virtual State<T>* getInitialState() = 0;
    virtual bool isGoal(State<T>*) = 0;
    virtual std::set<State<T>*> getAllPossibleStates(State<T>*) = 0;
};


#endif //SOLUTION_SERVER_SEARCHABLE_H
