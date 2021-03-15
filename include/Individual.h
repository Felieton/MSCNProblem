#ifndef MSCNProblem_INDIVIDUAL_H
#define MSCNProblem_INDIVIDUAL_H

#include "Table.h"
#include "Random.h"
#include "Const.h"
#include "MscnProblem.h"

class Individual {
private:
    Table<double> *solution;
public:
    Individual();
    Individual(Random *ran, int ind_size);
    ~Individual();

    Table<double>* getGenotype();
    double getGene(int index);
    double getFitness(Problem* problem);
};

#endif //MSCNProblem_INDIVIDUAL_H
