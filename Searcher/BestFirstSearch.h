//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_BESTFIRSTSEARCH_H
#define SOLUTION_SERVER_BESTFIRSTSEARCH_H

#include "PriorityQueueSearcher.h"
#include "State.h"
#include <set>

template <class T>
class BestFirstSearch : public PriorityQueueSearcher<T>{
    std::set<State<T>*> closed;
public:
    void markSolutionPath(State<T>* _goal);
    State<T>* search(Searchable<T> searchable) override;
    State<T>* popSameStateIfCostMore(State<T>* _state);
    void clearStates();
};

template <class T>
void BestFirstSearch<T>::markSolutionPath(State<T>* _goal) {
    // clear open and mark the solution
    PriorityQueueSearcher<T>::markSolutionPath(_goal);
}
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
          if (closed.find(s) != closed.end() && this->openContains(s)) {
            this->pushToOpenList(s);
          }

          // Otherwise, if this new path is better than previous one
          else {
              // pop the same state if it costs more
              State<T>* ss = popSameStateIfCostMore(s);
              if (ss != nullptr) {
                  // insert the better path-state
                  pushToOpenList(s);
              }
          }
        }
    }

    // didn't find a solution
    // free space
    clearStates();

    return nullptr;
}

template <class T>
State<T>* BestFirstSearch<T>::popSameStateIfCostMore(State<T>* _state) {
    State<T>* result = PriorityQueueSearcher<T>::popSameStateIfCostMore(_state);
    // if it is in open list
    if (result != nullptr) return result;

    // if it is in close
    for (auto x : closed) {
        if (*x == *_state) {
            if (x->getCost() > _state->getCost()) {
                closed.erase(x);
                return x;
            }
            break;
        }
    }

    // not in both
    return nullptr;
}

template <class T>
void BestFirstSearch<T>::clearStates() {
    PriorityQueueSearcher<T>::clearStates();
    // clear closed
    for (auto x : closed) {

        // if it's not in solution
        if (! x->getIsInSolution()) {
            delete x;
        }

    }
}

#endif //SOLUTION_SERVER_BESTFIRSTSEARCH_H
