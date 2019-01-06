//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_STATE_H
#define SOLUTION_SERVER_STATE_H

template <class T>
class State {
T state;
double cost;
State<T> cameFrom;

public:
    State(T _state, double _cost, State<T> &_cameFrom);

    T& getState();

    bool operator==(const State<T>& rhs);

};

template <class T>
State<T>::State(T _state, double _cost, State<T> &_cameFrom) {
    state = _state;
    cost = _cost;
    cameFrom = _cameFrom;
}

template <class T>
bool State<T>::operator==(const State<T> &rhs) {
    return this->getState() == rhs.getState();
}

template <class T>
T& State<T>::getState() {
    return state;
}

#endif //SOLUTION_SERVER_STATE_H
