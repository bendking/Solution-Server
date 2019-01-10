//
// Created by Yaron Israel on 2019-01-10.
//

#ifndef SOLUTION_SERVER_ASTAR_H
#define SOLUTION_SERVER_ASTAR_H

#include "Searcher.h"
#include "State.h"
#include "StateCompare.h"
#include "Searchable.h"
#include "MySearcher.h"
#include "PriorityQueueSearcher.h"
#include <queue>
#include <cfloat>

template <class T>
class AStar : public PriorityQueueSearcher<T>{

public:
    void processState(State<T>* _state, Searchable<T>& searchable);
};

template <class T>
void MySearcher<T>::addToOpenList(State<T>* _state) {

}

template <class T>
void AStar<T>::processState(State<T>* _state, Searchable<T>& searchable) {
    // get all childs
    std::set<State<T>*> expand = searchable.getAllPossibleStates(_state);

    // get the cost plus the minimum child
    double lowest = DBL_MAX;
    for (auto x : expand) {
        if (x -> getCost() < lowest) {
            lowest = x;
        }

        delete x;
    }
    _state -> setCost(lowest);

}

#endif //SOLUTION_SERVER_ASTAR_H
