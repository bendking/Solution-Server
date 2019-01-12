//
// Created by ben on 1/12/19.
//

#ifndef SOLUTION_SERVER_SEARCHERSOLVER_H
#define SOLUTION_SERVER_SEARCHERSOLVER_H

#include "Solver.h"
#include "../Searcher/State.h"
#include "../Searcher/Searcher.h"

template <class T>
class SearcherSolver : public Solver<Searchable<T>, State<T>*> {
private:
    Searcher<T>* searcher;
public:
    SearcherSolver();
    explicit SearcherSolver(Searcher<T>* _searcher);
    ~SearcherSolver() override;
    State<T>* solve(Searchable<T> searchable) override;
};

/*
 * Example:
 * SearcherSolver<Cell>* solver = new SearcherSolver<Cell>();
 * Solver<Searchable<Cell>, State<Cell>*>* searcherSolver = new SearcherSolver<Cell>(BreadthFS);
 */

#endif //SOLUTION_SERVER_SEARCHERSOLVER_H
