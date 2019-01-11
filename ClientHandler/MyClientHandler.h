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

    // Get next line from client
    inputLine = input->read();
    while (inputLine != "end") {

        // Check if exist in cache, if not, solve it
        if (cacheManager->exists(inputLine)) {
            outputLine = cacheManager->getSolution(inputLine);
        } else {
            outputLine = solver->solve(inputLine);
        }

        // Send Solution
        output->send(outputLine);
        // Save solution to map
        cacheManager->saveSolution(inputLine, outputLine);
        // Get next line from client
        inputLine = input->read();
    }

}

#endif //SOLUTION_SERVER_MYCLIENTHANDLER_H
