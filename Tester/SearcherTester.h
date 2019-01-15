//
// Created by ben on 1/11/19.
//

#ifndef SOLUTION_SERVER_SEARCHERTEST_H
#define SOLUTION_SERVER_SEARCHERTEST_H

#include "../Searcher/Searcher.h"
#include "../Searcher/BreadthFirstSearch.h"
#include "../Searcher/BestFirstSearch.h"
#include "../Searcher/DepthFirstSearch.h"
#include "../Searcher/AStar.h"
#include "../Searchable/Searchable.h"
#include "../Searchable/MatrixSearchable.h"
#include "../Solver/SearcherSolver.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <list>
#include <tuple>
#include <thread>

using namespace std;

class SearcherTester {
public:
    SearcherTester() = default;
    int** generate_matrix(int n, int m, int random_limit);
    tuple<int, int> run(Searcher<Cell>* searcher, Searchable<Cell>* searchable);
    void test();

    // Debug
    void test_bfs();
    void old_test();
};


#endif //SOLUTION_SERVER_SEARCHERTEST_H
