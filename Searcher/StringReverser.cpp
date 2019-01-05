//
// Created by Yaron Israel on 2019-01-04.
//

#include "StringReverser.h"


StringReverser::StringReverser(string str) {
    this->problem = str;
}

string StringReverser::solve() {
    solution = string(problem);
    std::reverse(solution.begin(), solution.end());
    return solution;
}