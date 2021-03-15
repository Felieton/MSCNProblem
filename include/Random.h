#ifndef MSCNProblem_RANDOM_H
#define MSCNProblem_RANDOM_H

#include <iostream>
#include "Matrix.h"
#include "Table.h"

class Random {
public:
    Random(int iSeed);
    ~Random();

    int randomInteger(int from, int to);
    double randomDouble(int from, int to);
    void fillMatrix(Matrix<double>* matrix, int from, int to);
    void randFillTable(Table<double>* table, int from, int to);

private:
    int seed;
};


#endif //MSCNProblem_RANDOM_H
