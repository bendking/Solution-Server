//
// Created by Yaron Israel on 2019-01-04.
//

#ifndef SOLUTION_SERVER_STRINGREVERSER_H
#define SOLUTION_SERVER_STRINGREVERSER_H

#include "../Solver/Solver.h"
#include <string>

using namespace std;

class StringReverser : public Solver<string, string> {

public:
    // reverse string
    string solve(string s);
};


#endif //SOLUTION_SERVER_STRINGREVERSER_H
