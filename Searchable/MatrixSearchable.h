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
    Cell* start;
    State<Cell>* createState(int i, int j, State<Cell>* father);
public:
    ~MatrixSearchable();

    // Default start and goal
    MatrixSearchable(int _rows, int _cols, int **_matrix);

    // With specific goal
    MatrixSearchable(int _rows, int _cols, int **_matrix, int iGoal, int jGoal);
    MatrixSearchable(int _rows, int _cols, int **_matrix, Cell* _goal);

    // With specific goal and start
    MatrixSearchable(int _rows, int _cols, int **_matrix, int iStart, int jStart, int iGoal, int jGoal);
    MatrixSearchable(int _rows, int _cols, int **_matrix, Cell* _start, Cell* _goal);

    State<Cell>* getInitialState() override;
    bool isGoal(State<Cell>*) override;
    std::set<State<Cell>*> getAllPossibleStates(State<Cell>*) override;
};

static void delete_matrix(int** matrix, int rows)
{
    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
}


#endif //SOLUTION_SERVER_MATRIXSEARCHABLE_H
