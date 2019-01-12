//
// Created by ben on 1/11/19.
//

#ifndef SOLUTION_SERVER_MYCLIENTHANDLER_H
#define SOLUTION_SERVER_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "../CacheManager/CacheManager.h"
#include "../Searcher/Searcher.h"
#include <string>


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

    void parseInput(string string1);

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

    // Get next line from client
    inputLine = input->read();
    while (inputLine != "end") {

        /*
        // Check if exist in cache, if not, solve it
        if (cacheManager->exists(inputLine)) {
            outputLine = cacheManager->getSolution(inputLine);
        } else {
            outputLine = solver->solve(inputLine);
        }
*/
        matrix += "$";
        matrix += inputLine;

        // Get next line from client
        inputLine = input->read();

    }



    // Send Solution
    output->send(outputLine);
    // Save solution to map
    cacheManager->saveSolution(inputLine, outputLine);


}

template<class Problem, class Solution>
void MyClientHandler<Problem, Solution>::parseInput(string string1) {

    // Get the rows based on the number of $
    int rowsCount = 0;
    for (auto x : string1) {
        if (x == '$') {
            rowsCount ++;
        }
    }
    // there are two extra because the last two lines
    rowsCount -= 2;

    // Get the cols based on the number of commas till the first $
    int colsCount = 0;
    for (auto x : string1) {
        if (x == ',') {
            colsCount ++;
        }
        if (x == '$') {
            break;
        }
    }

    // allocate the new matrix
    int** a = new int*[rowsCount];
    for(int i = 0; i < rowsCount; ++i)
        a[i] = new int[colsCount];

    // init matrix
    int k = 0;
    string temp = "";
    for (int i = 0; i < rowsCount; i++) {
        for (int j = 0; j < colsCount; j++) {
            string temp = "";
            while (true) {
                if (string1[k] == '$') {
                    k++;
                    break;
                }
                else if (string1[k] == ',') {
                    k++;
                    continue;
                }
                temp += string1[k];
            }
            a[i][j] = stoi(temp);
        }
    }


    // get the start and goal

    string start = "";
    string end = "";
    int b = 0;
    for(int i = string1.length()-1; i >= 0; i--){
        if (string1.at(i) == '$') {
            b ++;
            continue;
        }
        if (b == 0)
            end += string1[i];
        else if (b == 1)
            start += string1[i];
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
        if (x == ',') {
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
        if (x == ',') {
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
