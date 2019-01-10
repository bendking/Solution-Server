//
// Created by Yaron Israel on 2019-01-07.
//

#ifndef SOLUTION_SERVER_DEPTHFIRSTSEARCH_H
#define SOLUTION_SERVER_DEPTHFIRSTSEARCH_H

#include "MySearcher.h"


template <class T>
class DepthFirstSearch : public MySearcher<T> {
    std::deque<State<T>*> open;

public:
    State<T>* popOpenList();
    void addToOpenList(State<T>* _state);
    void clearStates();
};


template <class T>
State<T>* DepthFirstSearch<T>::popOpenList() {
    MySearcher<T>::evaluatedNodes++;

    State<T>* state = open.back();
    open.pop_back();
    //
    return state;
}

template <class T>
void DepthFirstSearch<T>::addToOpenList(State<T>* _state) {
    MySearcher<T>::open.push_back(_state);
}

template <class T>
void DepthFirstSearch<T>::clearStates() {
    MySearcher<T>::clearStates();

    // Clear open
    for (auto x : open) {
        // If it's not in solution, delete
        if (!x->isInSolution()) {
            delete x;
        }
    }
}
#endif //SOLUTION_SERVER_DEPTHFIRSTSEARCH_H
