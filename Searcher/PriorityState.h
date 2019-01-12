//
// Created by Yaron Israel on 2019-01-11.
//

#ifndef SOLUTION_SERVER_STATEWITHHEURISTIC_H
#define SOLUTION_SERVER_STATEWITHHEURISTIC_H

#include "State.h"

template <class T>
class PriorityState{
    double priority = 0;
    State<T>* state;
public:

    // C_tor
    PriorityState(State<T>* _state, double _heuristicCost) {
        setPriority(_heuristicCost);
        setState(_state);
    }

    // Setters
    void setState(State<T>* _state) {
     state = _state;
    }
    void setPriority(double _cost) {
        priority = _cost;
    }

    // Getters
    State<T>* getState() {
        return state;
    }
    double getPriority() {
        return priority;
    }
};


#endif //SOLUTION_SERVER_STATEWITHHEURISTIC_H
