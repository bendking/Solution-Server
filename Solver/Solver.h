//
// Created by Yaron Israel on 2019-01-04.
//

#ifndef SOLUTION_SERVER_SOLVER_H
#define SOLUTION_SERVER_SOLVER_H


template <class Problem, class Solution>
class Solver {
private:

public:
    virtual ~Solver() = 0;

    virtual Solution solve(Problem) = 0; // solves the problem
};


#endif //SOLUTION_SERVER_SOLVER_H
