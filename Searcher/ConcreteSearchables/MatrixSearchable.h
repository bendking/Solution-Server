//
// Created by Yaron Israel on 2019-01-11.
//

#ifndef SOLUTION_SERVER_MATRIXSEARCHABLE_H
#define SOLUTION_SERVER_MATRIXSEARCHABLE_H

#include "../Searchable.h"

class Location {
public:
    int i;
    int j;

    Location(int x,int y) {
        i = x;
        j = y;
    }

    bool operator==(Location& rhs) {
        return (rhs.i == i && rhs.j == j);
    }

};

class MatrixSearchable : public Searchable<Location> {


int **matrix;
int rows, cols;

State<Location>* createState(int i, int j, State<Location>* father);


public:
    MatrixSearchable(int _rows, int _cols, int **_matrix);

    State<Location>* getInitialState() override;
    bool isGoal(State<Location>*) override;
    std::set<State<Location>*> getAllPossibleStates(State<Location>*) override;
};



#endif //SOLUTION_SERVER_MATRIXSEARCHABLE_H
