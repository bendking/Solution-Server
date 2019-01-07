//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_SEARCHER_H
#define SOLUTION_SERVER_SEARCHER_H

#include "Searchable.h"
#include "State.h"

template <class T>
class Searcher {

public:
    //D_tor
    virtual ~Searcher() = default;

    // the search method
    virtual State<T>* search (Searchable<T> searchable) = 0;
    // get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated() = 0;

    // mark solution
    void markSolutionPath(State<T>* _goal);
};

template <class T>
void Searcher<T>::markSolutionPath(State<T>* _goal){
    State<T>* tmp = _goal;
    // mark the solution
    do {
        tmp->toggleIsInSolution();
        tmp = tmp->getCameFrom();
    } while (tmp != nullptr);

}

#endif //SOLUTION_SERVER_SEARCHER_H
