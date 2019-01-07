//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_BESTFIRSTSEARCH_H
#define SOLUTION_SERVER_BESTFIRSTSEARCH_H

#include "PriorityQueueSearcher.h"
#include "State.h"
#include "StateCompare.h"
#include <set>
#include <algorithm>

template <class T>
class BestFirstSearch : public PriorityQueueSearcher<T>{
    std::set<State<T>*> closed;
public:
    State<T>* search(Searchable<T> searchable) override;
    State<T>* popSameStateIfCostMore(State<T>* _state);
    void clearStates();
};

template <class T>
State<T>* BestFirstSearch<T>::search(Searchable<T> searchable) {
    pushToOpenList(searchable.getInitialState());

    while (this->openListSize() > 0) {
        State<T>* n = this->popOpenList();
        closed.insert(n);

        // If n is the goal state
        if (searchable.isGoal(n)) {
            foundSolution(n);
            clearStates();
            return n;
        }

        // Create n's successors
        std::set<State<T>*> successors = searchable.getAllPossibleStates(n);

        // For each successor s do:
        for (State<T>* s: successors) {

          // If s is not in CLOSED and s is not in OPEN:
          if (closed.end() != std::find_if(closed.begin(), closed.end(), StatePointerCompare<T>(s)) && this->openContains(s)) {
            this->pushToOpenList(s);
          }

          // Otherwise, if this new path is better than previous one
          else {
              // Pop the same state if it costs more
              State<T>* ss = popSameStateIfCostMore(s);
              if (ss != nullptr) {
                  // Insert the better path-state
                  pushToOpenList(s);
              }
          }
        }
    }

    // Didn't find a solution
    // Free space
    clearStates();

    return nullptr;
}

template <class T>
State<T>* BestFirstSearch<T>::popSameStateIfCostMore(State<T>* _state) {
    State<T>* result = PriorityQueueSearcher<T>::popSameStateIfCostMore(_state);
    // If it is in open list
    if (result != nullptr) return result;

    // If it is in close
    for (auto x : closed) {
        if (*x == *_state) {
            if (x->getCost() > _state->getCost()) {
                closed.erase(x);
                return x;
            }
            break;
        }
    }

    // If not in both
    return nullptr;
}

template <class T>
void BestFirstSearch<T>::clearStates() {
    PriorityQueueSearcher<T>::clearStates();
    // Clear closed
    for (auto x : closed) {
        // if it's not in solution, delete
        if (! x->isInSolution()) {
            delete x;
        }
    }
}

#endif //SOLUTION_SERVER_BESTFIRSTSEARCH_H
