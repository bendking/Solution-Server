//
// Created by Yaron Israel on 2019-01-07.
//

#ifndef SOLUTION_SERVER_BREADTHFIRSTSEARCH_H
#define SOLUTION_SERVER_BREADTHFIRSTSEARCH_H

#include "Searcher.h"
#include "State.h"
#include "MySearcher.h"
#include <set>

template <class T>
class BreadthFirstSearch : public MySearcher<T> {
    std::deque<State<T>*> open;

public:
    State<T>* popOpenList();
    void addToOpenList(State<T>* _state);
    void clearStates();
    bool isOpenEmpty();
};

template <class T>
State<T>* BreadthFirstSearch<T>::popOpenList()
{
    MySearcher<T>::evaluatedNodes++;

    State<T>* state = open.front();
    open.pop_front();

    return state;
}

template <class T>
void BreadthFirstSearch<T>::addToOpenList(State<T>* _state) {
    open.push_back(_state);
}

template <class T>
void BreadthFirstSearch<T>::clearStates()
{
    MySearcher<T>::clearStates();

    // Clear open
    for (auto x : open) {
        // If it's not in solution, delete
        if (!x->isInSolution()) {
            delete x;
        }
    }
}

template <class T>
bool BreadthFirstSearch<T>::isOpenEmpty()
{
    if (open.empty()) {
        return true;
    }
    return false;
}

#endif //SOLUTION_SERVER_BREADTHFIRSTSEARCH_H
