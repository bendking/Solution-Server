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
};


#endif //SOLUTION_SERVER_SEARCHER_H
