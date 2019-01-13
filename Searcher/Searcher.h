//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_SEARCHER_H
#define SOLUTION_SERVER_SEARCHER_H

#include "../Searchable/Searchable.h"
#include "State.h"
#include "../Solver/Solver.h"

template <class T>
class Searcher {

public:
    virtual ~Searcher() = default;
    virtual State<T>* search (Searchable<T>* searchable) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
   // void markSolutionPath(State<T>* _goal);
};

/*
template <class T>
void Searcher<T>::markSolutionPath(State<T>* _goal){
    State<T>* vertex = _goal;
    // Mark each vertex in the solution
    do {
        vertex->toggleInSolution();
        vertex = vertex->getCameFrom();
    } while (vertex != nullptr);

}
 */

#endif //SOLUTION_SERVER_SEARCHER_H
