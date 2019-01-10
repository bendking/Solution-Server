//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_MYSEARCHER_H
#define SOLUTION_SERVER_MYSEARCHER_H

#include "Searcher.h"
#include "State.h"
#include "StateCompare.h"
#include "Searchable.h"
#include "MySearcher.h"
#include <queue>

template <class T>
class PriorityQueueSearcher : public MySearcher<T>{
private:
    std::priority_queue<State<T>*, std::vector<State<T>*>, StateCompare<T>> priorityQueue;
public:

    // Queue manipulation
    State<T>* popOpenList();
    void addToOpenList(State<T>* _state);

    //State<T>* popSameStateIfCostMore(State<T>* _state);
    void clearStates();

};


template <class T>
State<T>* PriorityQueueSearcher<T>::popOpenList()
{
    MySearcher<T>::evaluatedNodes++;
    return priorityQueue.pop();
}

/*
template <class T>
bool PriorityQueueSearcher<T>::openContains(State<T>* _state) {
    return getSameState(_state) != nullptr;
}
*/
/*
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
*/
template <class T>
void PriorityQueueSearcher<T>::addToOpenList(State<T>* _state) {
    std::vector<State<T>*> vec;
    bool shouldPushState = true;
    // Iterate over the queue
    while (!priorityQueue.empty())
    {
        State<T>* current = priorityQueue.top();
        priorityQueue.pop();

        // Check if this is what we are looking for
        if (*current == *_state) {
            if (current->getCost() < _state->getCost()) {
                shouldPushState = false;
            } else {
                delete current;
            }
            break;
        }

        // save it so we can put it back later to queue
        vec.push_back(current);

    }

    if (shouldPushState) {
        priorityQueue.push(_state);
    }


    // Add states back
    for (auto x : vec) {
        priorityQueue.push(x);
    }

}


template <class T>
void PriorityQueueSearcher<T>::clearStates() {
    MySearcher<T>::clearStates();
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
