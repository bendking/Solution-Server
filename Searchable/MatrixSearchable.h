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
    Cell* goal;
    State<Cell>* createState(int i, int j, State<Cell>* father);
public:
    ~MatrixSearchable();

    MatrixSearchable(int _rows, int _cols, int **_matrix, Cell* _goal);
    MatrixSearchable(int _rows, int _cols, int **_matrix);
    MatrixSearchable(int _rows, int _cols, int **_matrix, int iGoal, int jGoal);

    State<Cell>* getInitialState() override;
    bool isGoal(State<Cell>*) override;
    std::set<State<Cell>*> getAllPossibleStates(State<Cell>*) override;
};



#endif //SOLUTION_SERVER_MATRIXSEARCHABLE_H
