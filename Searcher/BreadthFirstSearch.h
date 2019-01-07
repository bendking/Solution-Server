//
// Created by Yaron Israel on 2019-01-07.
//

#ifndef SOLUTION_SERVER_BREADTHFIRSTSEARCH_H
#define SOLUTION_SERVER_BREADTHFIRSTSEARCH_H

#include "Searcher.h"

template <class T>
class BreadthFirstSearch : Searcher<T> {

public:
    State<T>* search(Searchable<T> searchable) override;
};

template <class T>
State<T>* BreadthFirstSearch<T>::search(Searchable<T> searchable) {

}

#endif //SOLUTION_SERVER_BREADTHFIRSTSEARCH_H
