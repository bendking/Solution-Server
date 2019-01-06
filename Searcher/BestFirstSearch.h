//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_BESTFIRSTSEARCH_H
#define SOLUTION_SERVER_BESTFIRSTSEARCH_H

#include "MySearcher.h"
#include "State.h"
#include <set>

template <class T>
class BestFirstSearch : MySearcher<T>{

public:
    State<T> search(Searchable<T> searchable) override;
};

template <class T>
State<T> BestFirstSearch<T>::search(Searchable<T> searchable) {
    pushToOpenList(searchable.getInitialState());
    std::set<State<T>*> closed;

    while (this->openListSize() > 0) {
        State<T>* n = this->popOpenList();
        closed.insert(n);

        // If n is the goal state
        if (searchable.isGoal(n)) {
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
            //  If it is not in OPEN add it to OPEN.

            // Otherwise, adjust its priority in OPEN
            
          }
        }
    }
}


#endif //SOLUTION_SERVER_BESTFIRSTSEARCH_H
