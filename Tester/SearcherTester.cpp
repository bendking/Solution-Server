//
// Created by ben on 1/11/19.
//

#include "SearcherTester.h"


int **SearcherTester::generate_matrix(int rows, int cols, int random_limit) {
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            // Give value between -1 and limit
            matrix[i][j] = (rand() % (random_limit + 1)) - 1;
        }
    }

    return matrix;
}

void SearcherTester::delete_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;

}

tuple<int, int> SearcherTester::run(Searcher<Cell> *searcher, Searchable<Cell> *searchable) {
    int nodes_aggregate;
    int price_aggregate;
    State<Cell> *solution;

    // Run search 10 times
    for (int i = 0; i < 10; ++i) {
        solution = searcher->search(*searchable);
        nodes_aggregate += searcher->getNumberOfNodesEvaluated();
        price_aggregate += solution->getCost();
    }

    nodes_aggregate /= 10;
    price_aggregate /= 10;

    // Return tuples of averages
    return {nodes_aggregate, price_aggregate};
}

// BFS TEST
void SearcherTester::test_test()
{
    int number_of_matrixes = 10;

    Searcher<Cell>* BreadthFS = new BreadthFirstSearch<Cell>();
//    SearcherSolver<Cell>* searcher = new SearcherSolver<Cell>(BreadthFS);
//    Solver<Searchable<Cell>*, State<Cell>*>* searcherSolver = new SearcherSolver<Cell>(BreadthFS);
    vector<tuple<int, int>> BreadthFS_results = vector<tuple<int, int>>();

    int size;
    int matrix_sizes [10];
    vector<int**> matrixes;
    for (int i = 0; i < number_of_matrixes; ++i) {
        // Randomize size of matrix
        size = (rand() % 50) + 1 + 10;
        matrix_sizes[i] = size;

        // Generate searchable matrix
        int **matrix = generate_matrix(size, size, 10);
        MatrixSearchable* searchable = new MatrixSearchable(size, size, matrix);
        matrixes.push_back(matrix); // Keep for later

        // Get results for each algorithm
        BreadthFS_results.push_back(run(BreadthFS, searchable));
        delete searchable;
    }

    ofstream graphs_file("graphs.txt");
    ofstream solutions_file("solution.txt");

    int matrix_size;
    int** matrix;
    // Write to graphs file
    graphs_file << to_string(number_of_matrixes) << endl;
    for (int i = 0; i < number_of_matrixes; ++i)
    {
        // Write matrix stats
        matrix_size = matrix_sizes[i];
        matrix = matrixes[i];

        graphs_file << to_string(matrix_size) << endl;
        graphs_file << "0,0" << endl;
        graphs_file << to_string(--matrix_size) + "," + to_string(matrix_size) << endl;

        // Write matrix
        graphs_file.setf(ios::left);
        for (int n = 0; n < matrix_size; ++n) {
            for (int m = 0; m < matrix_size; ++m) {
                graphs_file << matrix[n][m];
            }
            // Drop line
            graphs_file << endl;
        }
    }

    // Write out solution file
    for (int i = 0; i < number_of_matrixes; ++i) {
        solutions_file << get<0>(BreadthFS_results[i]) << "," << get<0>(BreadthFS_results[i]) << endl;
    }

    // Close files
    graphs_file.close();
    solutions_file.close();

    // Delete objects
    delete BreadthFS;

    for (int i = 0; i < number_of_matrixes; ++i) {
        delete_matrix(matrixes[i], matrix_sizes[i]);
    }

}

// NEW TEST (as specified by Michael)
void SearcherTester::test()
{
    int number_of_matrixes = 10;

    // TODO (OFEK): Make it so there aren't any errors
    Searcher<Cell>* BreadthFS = new BreadthFirstSearch<Cell>();
    Searcher<Cell>* BestFS = new BestFirstSearch<Cell>();
    Searcher<Cell>* DFS = new DepthFirstSearch<Cell>();
    Searcher<Cell>* Astar = new AStar<Cell>();

    vector<tuple<int, int>> BreadthFS_results = vector<tuple<int, int>>();
    vector<tuple<int, int>> BestFS_results = vector<tuple<int, int>>();
    vector<tuple<int, int>> DFS_results = vector<tuple<int, int>>();
    vector<tuple<int, int>> Astar_results = vector<tuple<int, int>>();

    int size;
    int matrix_sizes [10];
    vector<int**> matrixes;
    for (int i = 0; i < number_of_matrixes; ++i) {
        // Randomize size of matrix
        size = (rand() % 50) + 1 + 10;
        matrix_sizes[i] = size;

        // Generate searchable matrix
        int **matrix = generate_matrix(size, size, 10);
        matrixes.push_back(matrix);
        MatrixSearchable *searchable = new MatrixSearchable(size, size, matrix);

        // Get results for each algorithm
        BreadthFS_results.push_back(run(BreadthFS, searchable));
        BestFS_results.push_back(run(BreadthFS, searchable));
        DFS_results.push_back(run(DFS, searchable));
        Astar_results.push_back(run(Astar, searchable));

        delete searchable;
    }

    ofstream graphs_file("graphs.txt");
    ofstream solutions_file("solution.txt");

    int matrix_size;
    int** matrix;
    // Write to graphs file
    graphs_file << to_string(number_of_matrixes) << endl;
    for (int i = 0; i < number_of_matrixes; ++i)
    {
        // Write matrix stats
        matrix_size = matrix_sizes[i];
        matrix = matrixes[i];

        graphs_file << to_string(matrix_size) << endl;
        graphs_file << "0,0" << endl;
        graphs_file << to_string(--matrix_size) + "," + to_string(matrix_size) << endl;

        // Write matrix
        graphs_file.setf(ios::left);
        for (int n = 0; n < matrix_size; ++n) {
            for (int m = 0; m < matrix_size; ++m) {
                graphs_file << matrix[n][m];
            }
            // Drop line
            graphs_file << endl;
        }
    }

    // Write out solution file
    for (int i = 0; i < number_of_matrixes; ++i)
    {
        solutions_file << get<0>(BreadthFS_results[i]) << "," << get<0>(BreadthFS_results[i]) << endl;
        solutions_file << get<0>(BestFS_results[i]) << "," << get<0>(BestFS_results[i]) << endl;
        solutions_file << get<0>(DFS_results[i]) << "," << get<0>(DFS_results[i]) << endl;
        solutions_file << get<0>(Astar_results[i]) << "," << get<0>(Astar_results[i]) << endl;
    }


    // Close files
    graphs_file.close();
    solutions_file.close();

    // Delete objects
    delete BreadthFS;
    delete BestFS;
    delete DFS;
    delete Astar;

    for (int i = 0; i < number_of_matrixes; ++i) {
        delete_matrix(matrixes[i], matrix_sizes[i]);
    }

}

// OLD TEST (as specified by Eli)
void SearcherTester::old_test()
 {
    Searcher<Cell> *BreadthFS = new BreadthFirstSearch<Cell>();
    Searcher<Cell> *BestFS = new BestFirstSearch<Cell>();
    Searcher<Cell> *DFS = new DepthFirstSearch<Cell>();
    Searcher<Cell> *Astar = new AStar<Cell>();

    list<tuple<int, int>> BreadthFS_results = list<tuple<int, int>>();
    list<tuple<int, int>> BestFS_results = list<tuple<int, int>>();
    list<tuple<int, int>> DFS_results = list<tuple<int, int>>();
    list<tuple<int, int>> Astar_results = list<tuple<int, int>>();

    int BreadthFS_nodes, BreadthFS_price = 0;
    int BestFS_nodes, BestFS_price = 0;
    int DFS_nodes, DFS_price = 0;
    int Astar_nodes, Astar_price = 0;

    tuple<int, int> result;
    // Test 10 times for each matrix with each algorithm
    for (int n = 10; n < 50; ++n) {
        for (int i = 0; i < 10; ++i) {
            // Generate searchable matrix
            int **matrix = generate_matrix(n, n, 10);
            MatrixSearchable *searchable = new MatrixSearchable(n, n, matrix);

            // Get results for each algorithm

            result = run(BreadthFS, searchable);
            BreadthFS_nodes += get<0>(result);
            BreadthFS_price += get<1>(result);

            result = run(BestFS, searchable);
            BestFS_nodes += get<0>(result);
            BestFS_price += get<1>(result);

            result = run(DFS, searchable);
            DFS_nodes += get<0>(result);
            DFS_price += get<1>(result);

            result = run(Astar, searchable);
            Astar_nodes += get<0>(result);
            Astar_price += get<1>(result);

            delete searchable;
            delete matrix;
        }

        // Push average of results
        BreadthFS_results.push_back({BreadthFS_nodes / 10, BreadthFS_price / 10});
        BestFS_results.push_back({BestFS_nodes / 10, BestFS_price / 10});
        DFS_results.push_back({DFS_nodes / 10, DFS_price / 10});
        Astar_results.push_back({Astar_nodes / 10, Astar_price / 10});

        // Reset aggregates
        BreadthFS_nodes, BestFS_nodes, DFS_nodes, Astar_nodes = 0;
        BreadthFS_nodes, BestFS_nodes, DFS_nodes, Astar_nodes = 0;
    }

    ofstream graphs_file("graphs.txt", fstream::app);
    ofstream solutions_file("solution.txt", fstream::app);

    // Write results to file

    delete BreadthFS;
    delete BestFS;
    delete DFS;
    delete Astar;
}
