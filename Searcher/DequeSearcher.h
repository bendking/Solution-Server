//
// Created by Yaron Israel on 2019-01-07.
//

#ifndef SOLUTION_SERVER_DEQUESEARCHER_H
#define SOLUTION_SERVER_DEQUESEARCHER_H

#include "Searcher.h"
#include "StateCompare.h"
#include <queue>
#include <algorithm>


template <class T>
class DequeSearcher : public Searcher<T> {
protected:
    std::set<State<T>*> closed;
    std::deque<State<T>*> open;

public:
    void clearStates();
    virtual State<T>* getNextElement() = 0;
    virtual void insertElementToOpen(State<T>* _state) = 0;
    void visit(State<T*> _state);
    bool hasVisited(State<T*> _state);
    State<T>* search(Searchable<T> searchable) override;

};

template <class T>
State<T>* DequeSearcher<T>::search(Searchable<T> searchable) {
    // Insert first element
    insertElementToOpen(searchable.getInitialState());

    while (!DequeSearcher<T>::open.empty()) {
        State<T*> node = getNextElement();

        if (searchable.isGoal(node)) {
            // TODO (OFEK): free up space!!!
            markSolutionPath(node);
            clearStates();
            return node;
        }

        std::set<State<T>*> expand = searchable.getAllPossibleStates();
        for (auto child : expand) {
            // If not visited
            if (! hasVisited(child)) {
                visit(child);
                // Add element to open list
                insertElementToOpen(child);
            }
        }
    }
}



template <class T>
void DequeSearcher<T>::clearStates(){
    // Clear closed
    for (auto x : closed) {
        // If it's not in solution, delete
        if (! x->isInSolution()) {
            delete x;
        }
    }

    // Clear open
    for (auto x : open) {
        // If it's not in solution, delete
        if (!x->isInSolution()) {
            delete x;
        }
    }
}


template <class T>
void DequeSearcher<T>::visit(State<T*> _state) {
    closed.insert(_state);
}

template <class T>
bool DequeSearcher<T>::hasVisited(State<T*> _state) {
   return closed.end() != std::find_if(closed.begin(), closed.end(), StatePointerCompare<T>(_state));
}

#endif //SOLUTION_SERVER_DEQUESEARCHER_H
