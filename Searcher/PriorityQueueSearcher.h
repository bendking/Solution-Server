//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_PRIORITYQUEUESEARCHER_H
#define SOLUTION_SERVER_PRIORITYQUEUESEARCHER_H

#include "Searcher.h"
#include "State.h"
#include "StateCompare.h"
#include "../Searchable/Searchable.h"
#include "MySearcher.h"
#include "PriorityState.h"
#include <queue>

template <class T>
class PriorityQueueSearcher : public MySearcher<T> {
private:
    std::priority_queue<PriorityState<T>*, std::vector<PriorityState<T>*>, PriorityStateCompare<T>> priorityQueue;
public:

    // Queue manipulation
    State<T>* popOpenList();
    void addToOpenList(State<T>* _state);
    void clearStates();
    bool isOpenEmpty();

    virtual double getPriorityOfState(State<T>* _state) = 0;

};


template <class T>
State<T>* PriorityQueueSearcher<T>::popOpenList()
{
    MySearcher<T>::evaluatedNodes++;

    PriorityState<T>* ps = priorityQueue.top();
    priorityQueue.pop();
    State<T>* s = ps->getState();
    delete(ps);
    return s;
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
void PriorityQueueSearcher<T>::addToOpenList(State<T>* _state)
{
    std::vector<PriorityState<T>*> vec;
    bool shouldPushState = true;
    PriorityState<T>* ps = new PriorityState<T>(_state, getPriorityOfState(_state));


    // Iterate over the queue
    while (!priorityQueue.empty())
    {
        PriorityState<T>* current = priorityQueue.top();


        // Check if this is what we are looking for
        if (*current->getState() == *_state) {
            if (current->getPriority() < ps->getPriority()) {
                shouldPushState = false;
            } else {
                priorityQueue.pop();
                delete current->getState();
                delete current;
            }
            break;
        }

        // Save it so we can put it back later to queue
        priorityQueue.pop();
        vec.push_back(current);

    }

    if (shouldPushState) {
        priorityQueue.push(ps);
    } else {
        delete _state;
        delete ps;
    }


    // Add states back
    for (auto x : vec) {
        priorityQueue.push(x);
    }

}


template <class T>
void PriorityQueueSearcher<T>::clearStates()
{
    MySearcher<T>::clearStates();

    // Iterate over the queue & delete unnecessary states
    while (!priorityQueue.empty())
    {
        // Get the top and pop
        PriorityState<T>* ps = priorityQueue.top();
        priorityQueue.pop();

        // Check if it in solution, if not, delete it
        if (!ps->getState()->isInSolution()) {
            delete ps->getState();
        }
        delete ps;

    }

}

template <class T>
bool PriorityQueueSearcher<T>::isOpenEmpty()
{
    if (priorityQueue.empty()) {
        return true;
    }
    return false;
}

#endif //SOLUTION_SERVER_PRIORITYQUEUESEARCHER_H
