//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_MYTESTCLIENTHANDLER_H
#define SOLUTION_SERVER_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "../CacheManager/CacheManager.h"
#include "../Searcher/StringReverser.h"
#include <string>


using namespace std;

template <class Problem, class Solution>
class MyTestClientHandler : public ClientHandler {
private:
    Solver<Problem, Solution>* solver;
    CacheManager* cacheManager;
public:
    // Constructor & Destructor
    MyTestClientHandler(Solver<Problem, Solution>* _solver, CacheManager* _cacheManager);
    ~MyTestClientHandler();

    // Implement ClientHandler
    void handleClient(InputStream *input, OutputStream *output);
};

//
// Implementation
// Note - this should be in cpp but it won't work there
//

template<class Problem, class Solution>
MyTestClientHandler<Problem, Solution>::MyTestClientHandler(Solver<Problem, Solution>* _solver, CacheManager* _cacheManager)
{
    solver = _solver;
    cacheManager = _cacheManager;
}

template<class Problem, class Solution>
MyTestClientHandler<Problem, Solution>::~MyTestClientHandler()
{
    delete solver;
    delete cacheManager;
}

template<class Problem, class Solution>
void MyTestClientHandler<Problem, Solution>::handleClient(InputStream *input, OutputStream *output)
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


#endif //SOLUTION_SERVER_MYTESTCLIENTHANDLER_H
