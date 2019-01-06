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
    std::set<State<T>> closed;

    while (this->openListSize() > 0) {
        State<T> n = this->popOpenList();
        closed.insert(n);

        if (searchable.isGoal(n)) {
            return n;
        }

        std::set<State<T>> succerssors = searchable.getAllPossibleStates(n);

        for (State<T> s: succerssors) {
           // Not finished
        }
    }
}


#endif //SOLUTION_SERVER_BESTFIRSTSEARCH_H
