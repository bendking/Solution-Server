//
// Created by Yaron Israel on 2019-01-07.
//

#ifndef SOLUTION_SERVER_DEPTHFIRSTSEARCH_H
#define SOLUTION_SERVER_DEPTHFIRSTSEARCH_H

#include "DequeSearcher.h"


template <class T>
class DepthFirstSearch : public DequeSearcher<T> {
public:
    State<T>* getNextElement();
    void insertElementToOpen(State<T>* _state);
};


template <class T>
State<T>* DepthFirstSearch<T>::getNextElement() {
    State<T>* state = DequeSearcher<T>::open.back();
    DequeSearcher<T>::open.pop_back();
    //
    return state;
}

template <class T>
void DepthFirstSearch<T>::insertElementToOpen(State<T>* _state) {
    DequeSearcher<T>::open.push_back(_state);
}

#endif //SOLUTION_SERVER_DEPTHFIRSTSEARCH_H
