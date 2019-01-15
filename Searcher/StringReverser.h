//
// Created by Yaron Israel on 2019-01-04.
//

#ifndef SOLUTION_SERVER_STRINGREVERSER_H
#define SOLUTION_SERVER_STRINGREVERSER_H

#include "../Solver/Solver.h"
#include <string>
#include <algorithm>

using namespace std;

class StringReverser : public Solver<string, string> {

public:
    // Reverse string given and return result
    string solve(string s);
    StringReverser* clone();
};


#endif //SOLUTION_SERVER_STRINGREVERSER_H
