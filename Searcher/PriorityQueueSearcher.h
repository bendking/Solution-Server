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
class PriorityQueueSearcher : public Searcher<T>{
private:
    int evaluatedNodes;
    std::priority_queue<State<T>*, std::vector<State<T>*>, StateCompare<T>> priorityQueue;
public:
    // Constructor & Destructor
    PriorityQueueSearcher();

    // Queue manipulation
    State<T>* popOpenList();
    void pushToOpenList(State<T>* _state);
    bool openContains(State<T>* _state);
    int openListSize();

    // Virtual
    virtual State<T>* popSameStateIfCostMore(State<T>* _state);
    virtual void clearStates();

    // Implement Searcher interface
    virtual State<T> search(Searchable<T> searchable) = 0;
    int getNumberOfNodesEvaluated();


};


template <class T>
PriorityQueueSearcher<T>::PriorityQueueSearcher() {
    evaluatedNodes = 0;
}

template <class T>
State<T>* PriorityQueueSearcher<T>::popOpenList()
{
    evaluatedNodes++;
    return priorityQueue.pop();
}

template <class T>
bool PriorityQueueSearcher<T>::openContains(State<T>* _state) {
    return getSameState(_state) != nullptr;
}

template <class T>
State<T>* PriorityQueueSearcher<T>::popSameStateIfCostMore(State<T>* _state)
{
    //std::priority_queue<State<T>*, std::vector<State<T>*>, StateCompare<T>> temp = priorityQueue;
    std::vector<State<T>*> vec;
    State<T>* result = nullptr;
    // Iterate over the queue
    while (!priorityQueue.empty())
    {
        State<T>* state = priorityQueue.top();

        // Check if this is what we are looking for
        if (*state == *_state) {
            if (state->getCost() > _state->getCost())
                result = state;
            break;
        }

        // Save it then  pop
        vec.push_back(state);
        priorityQueue.pop();
    }

    // Add states back
    for (auto x : vec) {
        priorityQueue.push(x);
    }

    // Return the result
    return result;
}
template <class T>
void PriorityQueueSearcher<T>::pushToOpenList(State<T>* _state) {
    priorityQueue.push(_state);
}

template <class T>
int PriorityQueueSearcher<T>::openListSize() {
    return  (int)priorityQueue.size();
}

template <class T>
int PriorityQueueSearcher<T>::getNumberOfNodesEvaluated() {
    return evaluatedNodes;
};


template <class T>
void PriorityQueueSearcher<T>::clearStates() {
    // Iterate over the queue & delete unnecessary states
    while (!priorityQueue.empty())
    {
        // Get the top and pop
        State<T>* state = priorityQueue.top();
        priorityQueue.pop();

        // Check if it in solution, if not, delete it
        if (!state->isInSolution()) {
            delete state;
        }

    }
}
#endif //SOLUTION_SERVER_MYSEARCHER_H
