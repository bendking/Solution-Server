//
// Created by Yaron Israel on 2019-01-04.
//

#ifndef SOLUTION_SERVER_STRINGREVERSER_H
#define SOLUTION_SERVER_STRINGREVERSER_H

#include "../Solver/Solver.h"
#include <string>

using namespace std;

class StringReverser : Solver<string, string> {
string problem;
string solution;
public:
    // C_tor
    StringReverser(string s);
    // reverse string
    string solve();
};


#endif //SOLUTION_SERVER_STRINGREVERSER_H
