//
// Created by Yaron Israel on 2019-01-06.
//

#ifndef SOLUTION_SERVER_STATE_H
#define SOLUTION_SERVER_STATE_H

template <class T>
class State {
private:
    T* state;
    double cost;
    State<T>* cameFrom = nullptr;
    bool inSolution = false;
public:

    // delete all chain of states from the heap (if allocated there)
    static void deleteChainOfStatesFromHeap(State<T>* state);

    State(T* _state, double _cost, State<T>* _cameFrom);
    ~State() { delete state; }

    // Getters & setters
    T* getState();
    double getCost();
    void setCost(double _cost);
    State<T>* getCameFrom();
    void setCameFrom(State<T>* _cameFrom);

    // Helpers
    void toggleInSolution();
    bool isInSolution();

    // Operators
    bool operator==(State<T>& rhs);
};

template <class T>
void State<T>::deleteChainOfStatesFromHeap(State<T>* state) {
    State<T>* temp;
    while (state != nullptr) {
        temp = state->getCameFrom();
        delete state;
        state = temp;
    }
}
template <class T>
State<T>::State(T* _state, double _cost, State<T>* _cameFrom)
{
    state = _state;
    cost = _cost;
    cameFrom = _cameFrom;
}

template <class T>
bool State<T>::operator==(State<T> &rhs) {
    return (*this->getState()) == (*rhs.getState());
}

template <class T>
T* State<T>::getState() {
    return state;
}

template <class T>
void State<T>::setCost(double _cost) {
    cost = _cost;
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
void State<T>::toggleInSolution() {
    inSolution = !inSolution;
}

template <class T>
bool State<T>::isInSolution() {
    return inSolution;
}

#endif //SOLUTION_SERVER_STATE_H
