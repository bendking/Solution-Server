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
class TestClientHandler : public ClientHandler {
private:
    Solver<Problem, Solution>* solver;
    CacheManager<string, string>* cacheManager;
public:
    // Constructor & Destructor
    TestClientHandler(Solver<Problem, Solution>* _solver, CacheManager<Problem, Solution>* _cacheManager);
    ~TestClientHandler() override;
    TestClientHandler<Problem, Solution>* clone() override;

    // Implement ClientHandler
    void handleClient(InputStream *input, OutputStream *output);
};

template<class Problem, class Solution>
TestClientHandler<Problem, Solution>::TestClientHandler(Solver<Problem, Solution>* _solver, CacheManager<Problem, Solution>* _cacheManager)
{
    solver = _solver;
    cacheManager = _cacheManager;
}

template<class Problem, class Solution>
TestClientHandler<Problem, Solution>::~TestClientHandler()
{
    delete solver;
}

template<class Problem, class Solution>
TestClientHandler<Problem, Solution>* TestClientHandler<Problem, Solution>::clone() {
    return new TestClientHandler(solver, cacheManager);
}

template<class Problem, class Solution>
void TestClientHandler<Problem, Solution>::handleClient(InputStream *input, OutputStream *output)
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
