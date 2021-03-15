#include "../include/Random.h"
#include <iostream>

Random::Random(int iSeed) {
    seed = iSeed;
    srand(seed);
}

Random::~Random() {
}

int Random::randomInteger(int from, int to) {
    return rand() % to + from;
}

double Random::randomDouble(int from, int to) {
    double ran = (double) rand() / RAND_MAX;
    return from + (ran * (to - from));
}

void Random::fillMatrix(Matrix<double>* matrix, int from, int to) {
    for (int i = 0; i < matrix->get_rows_amount(); i++) {
        for (int j = 0; j < matrix->get_columns_amount(); j++) {
            matrix->set(j, i, randomDouble(from, to));
        }
    }
}

void Random::randFillTable(Table<double>* table, int from, int to) {
    for (int i = 0; i < table->getSize(); i++) {
        table->set(i, randomDouble(from, to));
    }
}
