//
// Created by ben on 1/4/19.
//

#include "MyTestClientHandler.h"


MyTestClientHandler::MyTestClientHandler(Solver<string, string>* _solver, CacheManager* _cacheManager) {
    solver = _solver;
    cacheManager = _cacheManager;
}

MyTestClientHandler::~MyTestClientHandler() {
    delete solver;
    delete cacheManager;
}


// TO - THINK : WHO IS RESPONSIBLE FOR THE DELETION OF THE STREAMS?
void MyTestClientHandler::handleClient(InputStream *input, OutputStream *output)
{
   string inputLine, outputLine;

   // Get next line from client
   inputLine = input->read();

   while (inputLine != "end") {

       // Check if exist in cache, if not, solve it
       if (cacheManager->exists(inputLine)) {
           outputLine = cacheManager->getSolution(inputLine);
       } else {
           outputLine = solver -> solve(inputLine);
       }

       // Send Solution
       output->send(outputLine);

       // Get next line from client
       inputLine = input->read();
   }

}