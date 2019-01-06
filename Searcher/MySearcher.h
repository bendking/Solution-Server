//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_MYSEARCHER_H
#define SOLUTION_SERVER_MYSEARCHER_H

#include "Searcher.h"
#include "State.h"
#include "StateCompare.h"
#include "Searchable.h"
#include <queue>

template <class T>
class MySearcher : Searcher<T>{

    int evaluatedNodes;
    std::priority_queue<State<T>, std::vector<State<T>>, StateCompare<T>> myPriorityQueue;

public:

    MySearcher();

    State<T> popOpenList();
    void pushToOpenList(State<T> &_state);

    int openListSize();

    int getNumberOfNodesEvaluated();

    virtual State<T> search(Searchable<T> searchable) = 0;

};


template <class T>
MySearcher<T>::MySearcher() {
    evaluatedNodes = 0;
}

template <class T>
State<T> MySearcher<T>:: popOpenList(){
    evaluatedNodes++;
    return myPriorityQueue.pop();
}

template <class T>
void MySearcher<T>::pushToOpenList(State<T> &_state) {
    myPriorityQueue.push(_state);
}

template <class T>
int MySearcher<T>::openListSize() {
    return  (int)myPriorityQueue.size();
}

template <class T>
int MySearcher<T>::getNumberOfNodesEvaluated() {
    return evaluatedNodes;
};

#endif //SOLUTION_SERVER_MYSEARCHER_H
