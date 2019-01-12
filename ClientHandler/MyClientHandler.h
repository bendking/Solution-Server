//
// Created by ben on 1/11/19.
//

#ifndef SOLUTION_SERVER_MYCLIENTHANDLER_H
#define SOLUTION_SERVER_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "../CacheManager/CacheManager.h"
#include "../Searcher/Searcher.h"
#include <string>
#include <algorithm>


using namespace std;

template <class Problem, class Solution>
class MyClientHandler : public ClientHandler {
private:
    Solver<Problem, Solution>* solver;
    CacheManager<string, string>* cacheManager;
public:
    // Constructor & Destructor
    MyClientHandler(Solver<Problem, Solution>* _solver, CacheManager<Problem, Solution>* _cacheManager);
    ~MyClientHandler();

    // Implement ClientHandler
    void handleClient(InputStream *input, OutputStream *output);

    // Helpers
    void parseInput(string input);

};

template<class Problem, class Solution>
MyClientHandler<Problem, Solution>::MyClientHandler(Solver<Problem, Solution>* _solver, CacheManager<Problem, Solution>* _cacheManager)
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

    string matrix = "";
    string all_input = "";
    // Get next line from client

    inputLine = input->read();
    while (inputLine.find("end") != string::npos)
    {
        // Add input line to total input
        all_input += inputLine;

        // Get next line from client
        inputLine = input->read();

        /*
        // Check if exist in cache, if not, solve it
        if (cacheManager->exists(inputLine)) {
            outputLine = cacheManager->getSolution(inputLine);
        } else {
            outputLine = solver->solve(inputLine);
        }
        */
    }



    // Send Solution
    output->send(outputLine);
    // Save solution to map
    cacheManager->saveSolution(inputLine, outputLine);


}

template<class Problem, class Solution>
void MyClientHandler<Problem, Solution>::parseInput(string input)
{
    // Text info
    char line_end = '\n';
    char row_delim = ',';

    // Get the rows based on the number of \n
    int rows = 0;
    for (char x : input) {
        if (x == line_end) {
            ++rows;
        }
    }
    // There are three extra (entrance, exit, end)
    rows -= 3;

    // Get the cols based on the number of commas till the first \n
    int cols = 0;
    for (auto x : input) {
        if (x == row_delim) {
            ++cols;
        }
        if (x == line_end) {
            break;
        }
    }

    // Allocate the new matrix
    int** a = new int*[rows];
    for(int i = 0; i < rows; ++i)
        a[i] = new int[cols];

    // Initialize matrix values
    int k = 0;
    string num = "";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            num = "";
            while (true)
            {
                // If reached end of line, go to next line
                if (input[k] == line_end) {
                    ++k;
                    break;
                }
                // If reached delimiter, go to next number
                else if (input[k] == row_delim) {
                    ++k;
                    continue;
                }
                // Else, consider as part of number
                num += input[k];
            }
            // Put number in matrix
            a[i][j] = stoi(num);
        }
    }


    // get the start and goal TODO: CHECK

    string start = "";
    string end = "";
    int b = 0;
    for(int i = input.length()-1; i >= 0; i--){
        if (input.at(i) == line_end) {
            b ++;
            continue;
        }
        if (b == 0)
            end += input[i];
        else if (b == 1)
            start += input[i];
        else if (b == 2)
            break;
    }

    reverse(start.begin(), start.end());
    reverse(end.begin(), end.end());

    int iStart, jStart;
    int iGoal, jGoal;

    string tempI, tempJ;

    bool flag = true;
    for (auto x : start) {
        if (x == row_delim) {
            flag = !flag;
        }
        if (flag) {
            tempI += x;
        } else {
            tempJ += x;
        }
    }

    iStart = stoi(tempI);
    jStart = stoi(tempJ);

    tempI = "";
    tempJ = "";

    flag = true;
    for (auto x : start) {
        if (x == row_delim) {
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


    // We got everything
    // a is the matrix, iStart, jStart, iGoal, jGoal


}

#endif //SOLUTION_SERVER_MYCLIENTHANDLER_H
