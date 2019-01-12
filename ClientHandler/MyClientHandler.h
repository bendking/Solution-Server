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


using namespace std;

template <class Problem, class Solution>
class MyClientHandler : public ClientHandler {
private:
    Solver<Problem, Solution>* solver;
    CacheManager<string, string>* cacheManager;
public:
    // Constructor & Destructor                                    Subject to change
    MyClientHandler(Solver<Problem, Solution>* _solver, CacheManager<string, string>* _cacheManager);
    ~MyClientHandler();

    // Implement ClientHandler
    void handleClient(InputStream *input, OutputStream *output);

    // Helpers
    //   <matrix, size, end, start, matrix_string>
    tuple<int**, tuple<int,int>, tuple<int,int>, tuple<int,int>, string> parseInput(string input);
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
    delete cacheManager;
}

template<class Problem, class Solution>
void MyClientHandler<Problem, Solution>::handleClient(InputStream *input, OutputStream *output)
{
    string inputLine;
    string outputLine;

    string all_input = "";
    // Get next line from client
    inputLine = input->read();
    // Get rest of lines
    while (inputLine.find("end") != string::npos)
    {
        // Add input line to total input
        all_input += inputLine;
        // Get next line from client
        inputLine = input->read();
    }

    // Parse input into meaningful data
    auto data = parseInput(all_input);
    // Extract data
    int** matrix = get<0>(data);
    tuple<int,int> size = get<1>(data);
    tuple<int,int> start = get<2>(data);
    tuple<int,int> end = get<3>(data);
    string matrix_str = get<4>(data);

    string solution;
    // Check if problem exist in cache, if not, solve it
    if (cacheManager->exists(matrix_str)) {
        // Get solution from cache
        solution = cacheManager->getSolution(matrix_str);
    } else {
        // Solve problem and save in cache
        MatrixSearchable* searchable = new MatrixSearchable(get<0>(size), get<1>(size), matrix);
        State<Cell> cell = solver->solve(searchable);
        solution = extractSolution(cell);
        cacheManager->saveSolution(matrix_str, solution);
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

    string right = "right,";
    string left = "left,";
    string down = "down,";
    string up = "up,";

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
        else if ((origin_state->i > current_state->i) && (origin_state->j == current_state->j)) {
            solution_str.insert(0, down);
        }
        else if ((origin_state->i == current_state->i) && (origin_state->j == current_state->j)) {
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
    int cols = 0;
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

                // If reached end of line, go to next line
                if (input[k] == eol) {
                    ++k;
                    break;
                }
                // If reached delimiter, go to next number
                else if (input[k] == delim) {
                    ++k;
                    continue;
                }
                // Else, consider as part of number
                num += input[k];
            }
            // Put number in matrix
            matrix[i][j] = stoi(num);
        }
    }



    // Get starting index and goal index
    string start = "";
    string end = "";
    int lines_passed = 0;
    for(int i = input.length()-1; i >= 0; i--)
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

    // Parse start and end into proper numbers
    int iStart, jStart;
    int iGoal, jGoal;

    string tempI, tempJ;

    // Parse start
    bool flag = true;
    for (char x : start)
    {
        // If reached ','
        if (x == delim) {
            flag = !flag;
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

    iStart = stoi(tempI);
    jStart = stoi(tempJ);

    tempI, tempJ = "";

    // Parse end
    flag = true;
    for (char x : start) {
        if (x == delim) {
            flag = !flag;
        }
        if (flag) {
            tempI += x;
        } else {
            tempJ += x;
        }
    }

    iGoal = stoi(tempI);
    jGoal= stoi(tempJ);

    // Return tuple containing data
    return {matrix, {rows, cols}, {iStart, jStart}, {iGoal, jGoal}, matrix_str};
}

#endif //SOLUTION_SERVER_MYCLIENTHANDLER_H
