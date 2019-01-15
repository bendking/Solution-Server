//
// Created by Yaron Israel on 2019-01-07.
//

#ifndef SOLUTION_SERVER_MYSEARCHER_H
#define SOLUTION_SERVER_MYSEARCHER_H

#include "Searcher.h"
#include "StateCompare.h"
#include <queue>
#include <algorithm>


template <class T>
class MySearcher : public Searcher<T> {
protected:
    std::set<State<T>*> closed;
    int evaluatedNodes = 0;
    Searchable<T>* currentSearchable;
public:
    MySearcher<T>() = default;
    MySearcher<T>* clone() = 0;

    virtual void clearStates() = 0;
    virtual State<T>* popOpenList() = 0;
    virtual void addToOpenList(State<T>* _state) = 0;
    //virtual void processState(State<T>* _state, Searchable<T>& searchable) {};
    virtual bool isOpenEmpty() = 0;

    int getNumberOfNodesEvaluated() override;
    void visit(State<T>* _state);
    bool hasVisited(State<T>* _state);
    State<T>* search(Searchable<T>* searchable) override;
    void markSolutionPath(State<T>* _goal);
    void initMembers(Searchable<T>* searchable);

};

template <class T>
State<T>* MySearcher<T>::search(Searchable<T>* searchable)
{
    // Initialize members
    initMembers(searchable);

    // Insert first element
    addToOpenList(searchable->getInitialState());

    while (!isOpenEmpty()) {
        State<T>* node = popOpenList();

        if (searchable->isGoal(node)) {
            // Marks all states that n solution so they will not be deleted
            markSolutionPath(node);
            // Delete all states that are not in solution
            clearStates();
            return node;
        }

        // visit state
        visit(node);

        // Add its children
        std::set<State<T>*> expand = searchable->getAllPossibleStates(node);
        for (auto child : expand) {
            // If not visited
            if (!hasVisited(child)) {
                // Add element to open list
                addToOpenList(child);
            } else {
                // Delete unnecessary states
                delete child;
            }
        }
    }

    // Didn't find a solution
    clearStates();
    return nullptr;
}

template <class T>
void MySearcher<T>::clearStates()
{
    // Clear closed
    for (auto x : closed) {
        // If it's not in solution, delete
        if (!x->isInSolution() && x != nullptr) {
            delete x;
        }
    }

    closed.clear();
}

template <class T>
void MySearcher<T>::initMembers(Searchable<T>* searchable) {
    evaluatedNodes = 0;
    currentSearchable = searchable;
}
/*
template <class T>
void MySearcher<T>::clearStates(){
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
*/


template <class T>
void MySearcher<T>::visit(State<T>* _state) {
    closed.insert(_state);
}

template <class T>
bool MySearcher<T>::hasVisited(State<T>* _state) {
   return closed.end() != std::find_if(closed.begin(), closed.end(), StatePointerCompare<T>(_state));
}

template <class T>
int MySearcher<T>::getNumberOfNodesEvaluated() {
    return evaluatedNodes;
}


template <class T>
void MySearcher<T>::markSolutionPath(State<T>* _goal)
{
    State<T>* vertex = _goal;
    // Mark each vertex in the solution
    do {
        vertex->toggleInSolution();
        vertex = vertex->getCameFrom();
    } while (vertex != nullptr);

}
#endif //SOLUTION_SERVER_MYSEARCHER_H
