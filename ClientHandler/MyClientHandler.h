//
// Created by ben on 1/11/19.
//

#ifndef SOLUTION_SERVER_MYCLIENTHANDLER_H
#define SOLUTION_SERVER_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "../CacheManager/CacheManager.h"
#include "../Searcher/Searcher.h"
#include "../Searchable/MatrixSearchable.h"
#include <tuple>
#include <string>
#include <algorithm>
#include <iostream>


using namespace std;

template <class Problem, class Solution>
class MyClientHandler : public ClientHandler {
private:
    Solver<Problem, Solution>* solver;
    CacheManager<string, string>* cacheManager;
public:
    // Constructor & Destructor
    MyClientHandler(Solver<Problem, Solution>* _solver, CacheManager<string, string>* _cacheManager);
    ~MyClientHandler() override;
    MyClientHandler<Problem, Solution>* clone();

    // Implement ClientHandler
    void handleClient(InputStream *input, OutputStream *output) override;

    // Helpers
    //   <matrix, size, end, start, matrix_string>
    tuple<int**, tuple<int,int>, tuple<int,int>, tuple<int,int>, string> parseInput(string input);
    tuple<int,int> parsePoint(string point, char delim);
    string extractSolution(State<Cell>* cell);

};

template<class Problem, class Solution>
MyClientHandler<Problem, Solution>::MyClientHandler(Solver<Problem, Solution>* _solver, CacheManager<string, string>* _cacheManager)
{
    solver = _solver;
    cacheManager = _cacheManager;
}

template<class Problem, class Solution>
MyClientHandler<Problem, Solution>::~MyClientHandler()
{
    delete solver;
}

template<class Problem, class Solution>
MyClientHandler<Problem, Solution>* MyClientHandler<Problem, Solution>::clone() {
    return new MyClientHandler<Problem, Solution>(solver->clone(), cacheManager);
}


template<class Problem, class Solution>
void MyClientHandler<Problem, Solution>::handleClient(InputStream *input, OutputStream *output)
{
    string inputLine;
    string outputLine;

    string all_input = "";
    // Get next line from client
    inputLine = input->read();
    all_input += inputLine;
    // Get rest of lines
    while (inputLine.find("end") == string::npos)
    {
        // Get next line from client
        inputLine = input->read();
        // Add input line to total input
        all_input += inputLine;
    }

    // cout << all_input << endl;

    // Parse input into meaningful data
    auto data = parseInput(all_input);
    // Extract data
    int** matrix = get<0>(data);
    tuple<int,int> size = get<1>(data);
    tuple<int,int> start = get<2>(data);
    tuple<int,int> end = get<3>(data);
    string matrix_str = get<4>(data);

    MatrixSearchable* searchable;
    string solution;

    // Check if problem exist in cache, if not, solve it
    if (cacheManager->exists(matrix_str))
    {
        // Get solution from cache
        solution = cacheManager->getSolution(matrix_str);
        // Delete allocated matrix
        delete_matrix(matrix, get<0>(size));
    }
    else
    {
        // Solve problem and save in cache
        searchable = new MatrixSearchable(get<0>(size), get<1>(size), matrix);
        State<Cell>* cell = solver->solve(searchable);

        // If there's no solution
        if (cell == NULL) {
            solution = "-1";
        }
        // If there is a solution
        else {
            solution = extractSolution(cell);
            cacheManager->saveSolution(matrix_str, solution);
        }
        // Clean up
        State<Cell>::deleteStateChain(cell);
        delete searchable;
    }

    // Send Solution
    output->send(solution);
}

template<class Problem, class Solution>
string MyClientHandler<Problem, Solution>::extractSolution(State<Cell>* cell)
{
    // Solution-to-be
    string solution_str;

    // Get current and origin data
    State<Cell>* current = cell;
    Cell* current_state;
    State<Cell>* origin = cell->getCameFrom();
    Cell* origin_state;

    string right = "Right,";
    string left = "Left,";
    string down = "Down,";
    string up = "Up,";

    while (origin != nullptr)
    {
        current_state = current->getState();
        origin_state = origin->getState();

        if ((origin_state->i == current_state->i) && (origin_state->j < current_state->j)) {
            solution_str.insert(0, right);
        }
        else if ((origin_state->i == current_state->i) && (origin_state->j > current_state->j)) {
            solution_str.insert(0, left);
        }
        else if ((origin_state->i < current_state->i) && (origin_state->j == current_state->j)) {
            solution_str.insert(0, down);
        }
        else if ((origin_state->i > current_state->i) && (origin_state->j == current_state->j)) {
            solution_str.insert(0, up);
        }

        // Progress loop variables
        current = origin;
        origin = origin->getCameFrom();
    }

    // Remove last comma & return
    solution_str.pop_back();
    return solution_str;
}

template<class Problem, class Solution>
tuple<int**, tuple<int,int>, tuple<int,int>, tuple<int,int>, string> MyClientHandler<Problem, Solution>::parseInput(string input)
{
    // Text info
    char eol = '\n';  // End of line
    char delim = ','; // Line delimiter

    // Get the rows based on the number of \n
    int rows = 0;
    for (char x : input) {
        if (x == eol) {
            ++rows;
        }
    }
    // There are three extra (entrance, exit, end)
    rows -= 3;

    // Get the cols based on the number of commas till the first \n
    int cols = 1;
    for (auto x : input) {
        if (x == delim) {
            ++cols;
        }
        if (x == eol) {
            break;
        }
    }

    // Allocate the new matrix
    int** matrix = new int*[rows];
    for(int i = 0; i < rows; ++i)
        matrix[i] = new int[cols];

    // Get matrix string
    string matrix_str;
    // Initialize matrix values
    int k = 0;
    string num = "";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            num = "";
            while (true)
            {
                // Add every char to matrix string
                matrix_str += input[k];

                // If reached delimiter or end-of-line
                if (input[k] == delim || input[k] == eol) {
                    ++k;
                    break;
                }
                // Else, consider as part of number
                num += input[k];
                ++k;
            }
            // Put number in matrix
            matrix[i][j] = stoi(num);
        }
    }



    // Get starting index and goal index
    string start = "";
    string end = "";
    int lines_passed = 0;
    for(int i = input.length()-2; i >= 0; i--)
    {
        // If reached end of line,
        if (input.at(i) == eol) {
            ++lines_passed;
            continue;
        }
        if (lines_passed == 0) // End line
            continue;
        else if (lines_passed == 1) // Goal line
            end += input[i];
        else if (lines_passed == 2) // Start line
            start += input[i];
        else if (lines_passed == 3) // Done
            break;
    }

    reverse(start.begin(), start.end());
    reverse(end.begin(), end.end());

    tuple<int,int> start_point = parsePoint(start, delim);
    tuple<int,int> end_point = parsePoint(end, delim);


    // Return tuple containing data
    return {matrix, {rows, cols}, start_point, end_point, matrix_str};
}

template<class Problem, class Solution>
tuple<int,int> MyClientHandler<Problem, Solution>::parsePoint(string point, char delim)
{
    int i, j;
    string tempI, tempJ;

    // Parse start
    bool flag = true;
    for (char x : point)
    {
        // If reached ','
        if (x == delim) {
            flag = !flag;
            continue;
        }
        // If at first number
        if (flag) {
            tempI += x;
        }
            // If at second number
        else {
            tempJ += x;
        }
    }

    i = stoi(tempI);
    j = stoi(tempJ);

    return {i,j};
}



#endif //SOLUTION_SERVER_MYCLIENTHANDLER_H
