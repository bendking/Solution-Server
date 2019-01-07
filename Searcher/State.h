//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_STATE_H
#define SOLUTION_SERVER_STATE_H

template <class T>
class State {
T state;
double cost;
State<T>* cameFrom = nullptr;
bool isInSolution = false;


public:
    // C_tor
    State(T _state, double _cost, State<T> &_cameFrom);

    // getters, setters
    T& getState();
    double getCost();
    void setCameFrom(State<T>* _cameFrom);
    State<T>* getCameFrom();
    void toggleIsInSolution();
    bool getIsInSolution();

    // operator == override
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

template <class T>
double State<T>::getCost() {
    return cost;
}

template <class T>
void State<T>::setCameFrom(State<T> *_cameFrom) {
    cameFrom = _cameFrom;
}

template <class T>
State<T>* State<T>::getCameFrom() {
    return cameFrom;
}
template <class T>
void State<T>::toggleIsInSolution() {
    isInSolution = !isInSolution;
}

template <class T>
bool State<T>::getIsInSolution() {
    return isInSolution;
}

#endif //SOLUTION_SERVER_STATE_H
