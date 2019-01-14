//
// Created by ben on 1/12/19.
//

#ifndef SOLUTION_SERVER_SEARCHERSOLVER_H
#define SOLUTION_SERVER_SEARCHERSOLVER_H

#include "Solver.h"
#include "../Searcher/State.h"
#include "../Searcher/Searcher.h"

template <class T>
class SearcherSolver : public Solver<Searchable<T>*, State<T>*> {
private:
    Searcher<T>* searcher;
public:
    SearcherSolver() = default;
    explicit SearcherSolver(Searcher<T>* _searcher);
    ~SearcherSolver() override;
    State<T>* solve(Searchable<T>* searchable) override;
};

/*
 * Example:
 * SearcherSolver<Cell>* solver = new SearcherSolver<Cell>();
 * Solver<Searchable<Cell>, State<Cell>*>* searcherSolver = new SearcherSolver<Cell>(BreadthFS);
 */



template<class T>
SearcherSolver<T>::SearcherSolver(Searcher<T>* _searcher) {
    searcher = _searcher;
}

template<class T>
SearcherSolver<T>::~SearcherSolver() {
    delete searcher;
}

template<class T>
State<T>* SearcherSolver<T>::solve(Searchable<T>* searchable) {
    return searcher->search(searchable);
}

#endif //SOLUTION_SERVER_SEARCHERSOLVER_H
