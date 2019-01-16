//
// Created by ben on 1/11/19.
//

#include "SearcherTester.h"


int **bug_matrix () {
    int matrix1[3][3] = {{0,-1,5},{5,9,4},{4,4,0}};
    int **matrix = new int *[3];
    for (int i = 0; i < 3; ++i) {
        matrix[i] = new int[3];
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = matrix1[i][j] ;
        }
    }
    return matrix;
}


int **SearcherTester::generate_matrix(int rows, int cols, int random_limit) {
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            // Give value between -1 and limit
            matrix[i][j] = (rand() % (random_limit + 1) ) -1 ;
        //    cout << matrix[i][j] << " ";
        }
      //  cout << endl;
    }
    //cout << endl;

    // Make sure first cell & last cell are not -1
    matrix[0][0] = 0;
    matrix[rows - 1][cols - 1] = 0;

    return matrix;
}


tuple<int, int> SearcherTester::run(Searcher<Cell> *searcher, Searchable<Cell> *searchable) {
    int nodes_aggregate = 0;
    int price_aggregate = 0;
    State<Cell> *solution;

    // Run search 10 times
    for (int i = 0; i < 1; ++i) {
        solution = searcher->search(searchable);
        nodes_aggregate += searcher->getNumberOfNodesEvaluated();
        price_aggregate += solution->getCost();
    }
    //cout << "," <<nodes_aggregate;
    //nodes_aggregate /= 10;
    //price_aggregate /= 10;

    // Return tuples of averages
    return {price_aggregate, nodes_aggregate};
}


// NEW TEST (as specified by Michael)
void SearcherTester::test()
{
    // Change as required
    int number_of_matrixes = 10;

    Searcher<Cell>* BestFS = new BestFirstSearch<Cell>();
    Searcher<Cell>* BreadthFS = new BreadthFirstSearch<Cell>();
    Searcher<Cell>* DFS = new DepthFirstSearch<Cell>();
    Searcher<Cell>* Astar = new AStar<Cell>();

    vector<tuple<int, int>> BreadthFS_results = vector<tuple<int, int>>();
    vector<tuple<int, int>> BestFS_results = vector<tuple<int, int>>();
    vector<tuple<int, int>> DFS_results = vector<tuple<int, int>>();
    vector<tuple<int, int>> Astar_results = vector<tuple<int, int>>();

    vector<MatrixSearchable*>searchables;

    int size;
    int matrix_sizes [10];
    vector<int**> matrixes;
    for (int i = 0; i < number_of_matrixes; ++i) {
        // Randomize size of matrix
        size = (rand() % 5) + 1 + 5 * i;
        matrix_sizes[i] = size;

       // cout << size;

        // Generate searchable matrix
        int **matrix = generate_matrix(size, size, 10);
        matrixes.push_back(matrix);
        MatrixSearchable *searchable = new MatrixSearchable(size, size, matrix);

        // Get results for each algorithm
        BreadthFS_results.push_back(run(BreadthFS, searchable));
        BestFS_results.push_back(run(BestFS, searchable));
        DFS_results.push_back(run(DFS, searchable));
        Astar_results.push_back(run(Astar, searchable));

        //cout << "Test " << i + 1 << " done." << endl;
       // cout << endl;
        searchables.push_back(searchable);
        //delete searchable;
    }

    ofstream graphs_file("graphs.txt");
    ofstream solutions_file("solution.txt");

    // Write to graphs file //

    // Needed variables
    int matrix_size;
    int** matrix;
    // Write number of matrixes
    graphs_file << to_string(number_of_matrixes) << endl;

    // Write all matrixes
    for (int i = 0; i < number_of_matrixes; ++i)
    {
        // Write matrix stats
        matrix_size = matrix_sizes[i];
        matrix = matrixes[i];

        graphs_file << to_string(matrix_size) << "," << to_string(matrix_size) << endl;
        graphs_file << "0,0" << endl;
        graphs_file << matrix_size-1 << "," << matrix_size-1 << endl;

        // Write matrix
        for (int n = 0; n < matrix_size; n++) {
            for (int m = 0; m < matrix_size - 1; m++) {
                graphs_file << setw(2) << matrix[n][m] << setw(1) << ",";
            }
            // Write last cell & drop line
            graphs_file << setw(2) << matrix[n][matrix_size-1] << endl;
        }
    }

    // Write out solution file
    for (int i = 0; i < number_of_matrixes; ++i)
    {
        solutions_file << get<0>(BestFS_results[i]) << "," << get<1>(BestFS_results[i]) << endl;
        solutions_file << get<0>(DFS_results[i]) << "," << get<1>(DFS_results[i]) << endl;
        solutions_file << get<0>(BreadthFS_results[i]) << "," << get<1>(BreadthFS_results[i]) << endl;
        solutions_file << get<0>(Astar_results[i]) << "," << get<1>(Astar_results[i]) << endl;
    }


    // Close files
    graphs_file.close();
    solutions_file.close();

    // Delete objects
    delete BreadthFS;
    delete BestFS;
    delete DFS;
    delete Astar;


    /*
    for (int i = 0; i < number_of_matrixes; ++i) {
        delete_matrix(matrixes[i], matrix_sizes[i]);
    }
     */

    for (auto x : searchables) {
        delete(x);
    }

}

// BFS TEST
void SearcherTester::test_bfs() {
    int number_of_matrixes = 10;

    // Unexplained bug
    Searcher<Cell>* BreadthFS = new BreadthFirstSearch<Cell>();
//    SearcherSolver<Cell>* searcher = new SearcherSolver<Cell>(BreadthFS);
//    Solver<Searchable<Cell>*, State<Cell>*>* searcherSolver = new SearcherSolver<Cell>(BreadthFS);

    vector<tuple<int, int>> BreadthFS_results = vector<tuple<int, int>>();

    int size;
    int matrix_sizes[10];
    vector<int **> matrixes;
    for (int i = 0; i < number_of_matrixes; ++i) {
        // Randomize size of matrix
        size = (rand() % 50) + 1 + 10;
        matrix_sizes[i] = size;

        // Generate searchable matrix
        int **matrix = generate_matrix(size, size, 10);
        MatrixSearchable *searchable = new MatrixSearchable(size, size, matrix);
        matrixes.push_back(matrix); // Keep for later

        // Get results for each algorithm
        BreadthFS_results.push_back(run(BreadthFS, searchable));
        delete searchable;
    }

    ofstream graphs_file("graphs.txt");
    ofstream solutions_file("solution.txt");

    int matrix_size;
    int **matrix;
    // Write to graphs file
    graphs_file << to_string(number_of_matrixes) << endl;
    for (int i = 0; i < number_of_matrixes; ++i) {
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
        solutions_file << get<0>(BreadthFS_results[i]) << "," << get<1>(BreadthFS_results[i]) << endl;
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
