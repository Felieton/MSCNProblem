#include "../include/Individual.h"

Individual::Individual() {
    solution = new Table<double>(0);
}

Individual::Individual(Random *ran, int ind_size) {
    solution = new Table<double>(ind_size);
    ran->randFillTable(solution, 0, X_MAX);
}

Individual::~Individual() {
    delete solution;
}

Table<double>* Individual::getGenotype() {
    return solution;
}

double Individual::getGene(int index) {
    return solution->get(index);
}

double Individual::getFitness(Problem* problem) {
    problem->initSolution(solution);
    return problem->getQuality();
}

