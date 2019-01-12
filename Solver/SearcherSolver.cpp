//
// Created by ben on 1/12/19.
//

#include "SearcherSolver.h"

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