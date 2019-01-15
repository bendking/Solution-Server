//
// Created by Yaron Israel on 2019-01-04.
//

#ifndef SOLUTION_SERVER_SOLVER_H
#define SOLUTION_SERVER_SOLVER_H


template <class Problem, class Solution>
class Solver {
public:
    virtual ~Solver() = default;
    virtual Solution solve(Problem) = 0;

    // Clone method: stateless - should return self, stateful - should return a clone of self
    virtual Solver<Problem, Solution>* clone() = 0;
};


#endif //SOLUTION_SERVER_SOLVER_H
