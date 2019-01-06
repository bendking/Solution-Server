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
    std::priority_queue<State<T>*, std::vector<State<T>*>, StateCompare<T>> myPriorityQueue;

public:

    // C_tor
    MySearcher();

    // Queue stuff
    State<T>* popOpenList();
    void pushToOpenList(State<T>* _state);
    bool openContains(State<T>* _state);
    int openListSize();
    State<T>* getSameState(State<T>* _state);

    int getNumberOfNodesEvaluated();

    // Implement Searcher interface
    virtual State<T> search(Searchable<T> searchable) = 0;

};


template <class T>
MySearcher<T>::MySearcher() {
    evaluatedNodes = 0;
}

template <class T>
State<T>* MySearcher<T>::popOpenList(){
    evaluatedNodes++;
    return myPriorityQueue.pop();
}

template <class T>
bool MySearcher<T>::openContains(State<T>* _state) {
    return getSameState(_state) != nullptr;
}

template <class T>
State<T>* MySearcher<T>::getSameState(State<T>* _state) {
    std::priority_queue<State<T>*, std::vector<State<T>*>, StateCompare<T>> temp = myPriorityQueue;

    // iterate over the queue
    while (!temp.empty()) {
        State<T>* s = temp.top();

        // Check if this is what we are looking for
        if (*s == *_state) {
            return s;
        }

        // Get the next one
        temp.pop();
    }

    // Didn't find
    return nullptr;
}
template <class T>
void MySearcher<T>::pushToOpenList(State<T>* _state) {
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
