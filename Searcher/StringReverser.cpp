//
// Created by Yaron Israel on 2019-01-04.
//

#include "StringReverser.h"



string StringReverser::solve(string problem) {
    string solution;
    solution = string(problem);
    std::reverse(solution.begin(), solution.end());
    return solution;
}