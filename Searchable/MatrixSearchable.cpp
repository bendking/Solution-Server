//
// Created by Yaron Israel on 2019-01-11.
//

#include "MatrixSearchable.h"

MatrixSearchable::~MatrixSearchable() {
    delete(goal);
    // SHOULD DELETE MATRIX TOO???
}

MatrixSearchable::MatrixSearchable(int _rows, int _cols, int **_matrix, Cell* _goal)
{
    rows = _rows;
    cols = _cols;
    matrix = _matrix;
    goal = _goal;
}

MatrixSearchable::MatrixSearchable(int _rows, int _cols, int **_matrix)
{
    rows = _rows;
    cols = _cols;
    matrix = _matrix;
    goal = new Cell(rows - 1, cols - 1);
}
MatrixSearchable::MatrixSearchable(int _rows, int _cols, int **_matrix, int iGoal, int jGoal) {
    rows = _rows;
    cols = _cols;
    matrix = _matrix;
    goal = new Cell(iGoal, jGoal);
}
State<Cell>* MatrixSearchable::getInitialState() {
    return createState(0, 0, nullptr);
}


bool MatrixSearchable::isGoal(State<Cell>* state)
{
    // Get where is the state
    Cell *arr = (state->getState());
    int i = arr->i;
    int j = arr->j;

    // Check if they are in N-1, N-1
    if (*arr == *goal) {
        return true;
    }

    return false;
}

std::set<State<Cell>*> MatrixSearchable::getAllPossibleStates(State<Cell>* state)
{
    // Get where is the state
    Cell *arr = (state->getState());
    int i = arr->i;
    int j = arr->j;

    std::set<State<Cell>*> result;

    if (i != 0) {
        result.insert(createState(i-1, j, state));
    }
    if (j != 0) {
        result.insert(createState(i, j-1, state));
    }
    if (i != rows-1) {
        result.insert(createState(i+1, j, state));
    }
    if (j != cols-1) {
        result.insert(createState(i, j+1, state));
    }

    return result;
}

State<Cell>* MatrixSearchable::createState(int i, int j, State<Cell>* father)
{

    Cell *cell = new Cell(i, j);

    double fathersCost = 0;
    if (father != nullptr) {
        fathersCost = father->getCost();
    }

    double cost = matrix[i][j] + fathersCost;
    return new State<Cell>(cell, cost, father);
}