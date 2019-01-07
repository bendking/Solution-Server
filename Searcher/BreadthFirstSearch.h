//
// Created by Yaron Israel on 2019-01-07.
//

#ifndef SOLUTION_SERVER_BREADTHFIRSTSEARCH_H
#define SOLUTION_SERVER_BREADTHFIRSTSEARCH_H

#include "Searcher.h"
#include "State.h"
#include "DequeSearcher.h"
#include <set>

template <class T>
class BreadthFirstSearch : public DequeSearcher<T> {

public:
    State<T>* getNextElement();
    void insertElementToOpen(State<T>* _state);
};

template <class T>
State<T>* BreadthFirstSearch<T>::getNextElement() {
    State<T>* s = DequeSearcher<T>::open.front();
    DequeSearcher<T>::open.pop_front();

    return s;
}

template <class T>
void BreadthFirstSearch<T>::insertElementToOpen(State<T>* _state) {
    DequeSearcher<T>::open.push_back(_state);
}


#endif //SOLUTION_SERVER_BREADTHFIRSTSEARCH_H
