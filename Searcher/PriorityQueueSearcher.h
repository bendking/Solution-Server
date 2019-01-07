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
class PriorityQueueSearcher : Searcher<T>{

    int evaluatedNodes;
    std::priority_queue<State<T>*, std::vector<State<T>*>, StateCompare<T>> myPriorityQueue;

public:

    // C_tor
    PriorityQueueSearcher();

    // Queue stuff
    State<T>* popOpenList();
    void pushToOpenList(State<T>* _state);
    bool openContains(State<T>* _state);
    int openListSize();
    State<T>* getSameState(State<T>* _state);

    int getNumberOfNodesEvaluated();
    virtual void foundSolution(State<T>* _goal);

    // Implement Searcher interface
    virtual State<T> search(Searchable<T> searchable) = 0;

};


template <class T>
PriorityQueueSearcher<T>::PriorityQueueSearcher() {
    evaluatedNodes = 0;
}

template <class T>
State<T>* PriorityQueueSearcher<T>::popOpenList(){
    evaluatedNodes++;
    return myPriorityQueue.pop();
}

template <class T>
bool PriorityQueueSearcher<T>::openContains(State<T>* _state) {
    return getSameState(_state) != nullptr;
}

template <class T>
State<T>* PriorityQueueSearcher<T>::getSameState(State<T>* _state) {
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
void PriorityQueueSearcher<T>::pushToOpenList(State<T>* _state) {
    myPriorityQueue.push(_state);
}

template <class T>
int PriorityQueueSearcher<T>::openListSize() {
    return  (int)myPriorityQueue.size();
}

template <class T>
int PriorityQueueSearcher<T>::getNumberOfNodesEvaluated() {
    return evaluatedNodes;
};

template <class T>
void PriorityQueueSearcher<T>::foundSolution(State<T>* _goal){
    State<T>* tmp = _goal;
    // mark the solution
    do {
        tmp->toggleIsInSolution();
        tmp = tmp->getCameFrom();
    } while (tmp != nullptr);

    // delete open list
    // iterate over the queue
    while (!myPriorityQueue.empty()) {

        // Get the top and pop
        State<T>* s = myPriorityQueue.top();
        myPriorityQueue.pop();

        // Check if it in solution, if not, delete it
        if (! s->getIsInSolution()) {
            delete s;
        }

    }

}
#endif //SOLUTION_SERVER_MYSEARCHER_H
