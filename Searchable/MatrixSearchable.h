//
// Created by Yaron Israel on 2019-01-11.
//

#ifndef SOLUTION_SERVER_MATRIXSEARCHABLE_H
#define SOLUTION_SERVER_MATRIXSEARCHABLE_H

#include "Searchable.h"

class Cell {
public:
    int i;
    int j;

    Cell(int x,int y)
    {
        i = x;
        j = y;
    }

    bool operator==(Cell& rhs) {
        return (rhs.i == i && rhs.j == j);
    }

};

class MatrixSearchable : public Searchable<Cell> {
private:
    int **matrix;
    int rows, cols;
    State<Cell>* createState(int i, int j, State<Cell>* father);
public:
    MatrixSearchable(int _rows, int _cols, int **_matrix);
    State<Cell>* getInitialState() override;
    bool isGoal(State<Cell>*) override;
    std::set<State<Cell>*> getAllPossibleStates(State<Cell>*) override;
};



#endif //SOLUTION_SERVER_MATRIXSEARCHABLE_H
