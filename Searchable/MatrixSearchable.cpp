//
// Created by Yaron Israel on 2019-01-11.
//

#include "MatrixSearchable.h"

MatrixSearchable::~MatrixSearchable() {
    delete(goal);
    delete(start);
    delete_matrix(matrix, rows);
}

MatrixSearchable::MatrixSearchable(int _rows, int _cols, int **_matrix, Cell* _goal)
{
    rows = _rows;
    cols = _cols;
    matrix = _matrix;
    start = new Cell(0,0);
    goal = _goal;
}

MatrixSearchable::MatrixSearchable(int _rows, int _cols, int **_matrix)
{
    rows = _rows;
    cols = _cols;
    matrix = _matrix;
    start = new Cell(0,0);
    goal = new Cell(rows - 1, cols - 1);

}

MatrixSearchable::MatrixSearchable(int _rows, int _cols, int **_matrix, int iGoal, int jGoal) {
    rows = _rows;
    cols = _cols;
    matrix = _matrix;
    start = new Cell(0,0);
    goal = new Cell(iGoal, jGoal);

}

MatrixSearchable::MatrixSearchable(int _rows, int _cols, int **_matrix, int iStart, int jStart, int iGoal, int jGoal) {
    rows = _rows;
    cols = _cols;
    matrix = _matrix;
    start = new Cell(iStart, jStart);
    goal = new Cell(iGoal, jGoal);
}

MatrixSearchable::MatrixSearchable(int _rows, int _cols, int **_matrix, Cell* _start, Cell* _goal) {
    rows = _rows;
    cols = _cols;
    matrix = _matrix;
    start = _start;
    goal = _goal;
}

MatrixSearchable::MatrixSearchable(int _rows, int _cols, int **_matrix, tuple<int,int> _start, tuple<int,int> _goal) {
    rows = _rows;
    cols = _cols;
    matrix = _matrix;
    start = new Cell(get<0>(_start), get<1>(_start));
    goal = new Cell(get<0>(_goal), get<1>(_goal));
}

State<Cell>* MatrixSearchable::getInitialState() {
    return createState(start->i, start->j, nullptr);
}


bool MatrixSearchable::isGoal(State<Cell>* state)
{
    // Get where is the state
    Cell *arr = (state->getState());

    // Check if they are in goal
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
    if (matrix[i][j] == -1) {
        return result;
    }

    State<Cell>* s;
    if (i != 0) {
        s = createState(i-1, j, state);
        if (s != nullptr)
            result.insert(s);
    }

    if (j != 0) {
        s = createState(i, j-1, state);
        if (s != nullptr)
            result.insert(s);
    }

    if (i != rows-1) {
        s = createState(i+1, j, state);
        if (s != nullptr)
            result.insert(s);
    }

    if (j != cols-1) {
        s = createState(i, j+1, state);
        if (s != nullptr)
            result.insert(s);
    }

    return result;
}

State<Cell>* MatrixSearchable::createState(int i, int j, State<Cell>* father)
{
    /*
    // Check if it is a wall
    if (matrix[i][j] == -1) {
        return nullptr;
    }
*/
    Cell *cell = new Cell(i, j);

    double fathersCost = 0;
    if (father != nullptr) {
        fathersCost = father->getCost();
    }

    double cost = matrix[i][j] + fathersCost;
    return new State<Cell>(cell, cost, father);
}