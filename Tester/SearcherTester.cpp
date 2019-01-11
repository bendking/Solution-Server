//
// Created by ben on 1/11/19.
//

#include "SearcherTester.h"


SearcherTester::SearcherTester() {

}

int** SearcherTester::generate_matrix(int rows, int cols, int random_limit)
{
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            // Give value between -1 and limit
            matrix[i][j] = (rand() % random_limit + 1) - 1;
        }
    }
}

void SearcherTester::delete_matrix(int** matrix, int rows)
{
    for (int i = 0; i < rows; ++i)
        delete [] matrix[i];
    delete [] matrix;

}

tuple<int, int> SearcherTester::run(Searcher<Cell>* searcher, Searchable<Cell>* searchable)
{
    State<Cell>* solution = searcher->search(*searchable);
    int evaluated_nodes = searcher->getNumberOfNodesEvaluated();
    int solution_price = solution->getCost();
    tuple<int,int> result = tuple<int,int>(evaluated_nodes, solution_price);
    return result;
}

void SearcherTester::test()
{
    // TODO (OFEK): Make it so there aren't any errors
    Searcher<Cell>* BreatdthFS = new BreadthFirstSearch<Cell>();
    Searcher<Cell>* BestFS = new BestFirstSearch<Cell>();
    Searcher<Cell>* DFS = new DepthFirstSearch<Cell>();
    Searcher<Cell>* Astar = new AStar<Cell>();

    list<tuple<int,int>> BreadthFS_results;
    list<tuple<int,int>> BestFS_results;
    list<tuple<int,int>> DFS_results;
    list<tuple<int,int>> AStar_results;

    // TODO: Open files

    list<tuple
    // Test 10 times for each matrix with each algorithm
    for (int n = 10; n < 50; n += 5)
    {
        int aggregate;
        int** matrix = generate_matrix(n, n, 10);
        for (int i = 0; i < 10; ++i) {

        }
    }

    // TODO: Write results to file

    delete BreatdthFS;
    delete BestFS;
    delete DFS;
    delete Astar;
}