//
// Created by Yaron Israel on 2019-01-10.
//

#ifndef SOLUTION_SERVER_ASTAR_H
#define SOLUTION_SERVER_ASTAR_H

#include "Searcher.h"
#include "State.h"
#include "StateCompare.h"
#include "../Searchable/Searchable.h"
#include "MySearcher.h"
#include "PriorityQueueSearcher.h"
#include <queue>
#include <cfloat>

template <class T>
class AStar : public PriorityQueueSearcher<T>{

public:
    //void processState(State<T>* _state, Searchable<T>& searchable);
    double getPriorityOfState(State<T>* _state);
};


template <class T>
double AStar<T>::getPriorityOfState(State<T>* _state) {

    // Get all children
    std::set<State<T>*> expand = MySearcher<T>::currentSearchable->getAllPossibleStates(_state);
    // Get the cost plus the minimum child
    double lowest = DBL_MAX;

    for (auto x : expand) {
        if (x -> getCost() < lowest) {
            lowest = x -> getCost();
        }

        delete x;
    }

    if (lowest == DBL_MAX) {
        lowest = _state->getCost();
    }

    return lowest ;


}


#endif //SOLUTION_SERVER_ASTAR_H
