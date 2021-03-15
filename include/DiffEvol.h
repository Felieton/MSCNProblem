#ifndef MSCNProblem_DIFFEVOL_H
#define MSCNProblem_DIFFEVOL_H

#include "MscnProblem.h"
#include "Table.h"
#include "Random.h"
#include "Individual.h"
#include "Optimizer.h"

class DiffEvol : public Optimizer {
private:
    double cross_prob;
    double diff_weight;

    Problem *problem;
    Table<Individual*> *population;
    Random *ran;
public:
    DiffEvol();
    DiffEvol(Problem* nproblem, Random* nran, int size_of_population, double ncross_prob,
            double ndiff_weight, bool& correct_param);
    ~DiffEvol();

    double compute() override;
    bool generatePopulation();
    Individual * getRandomInd();
    bool indAreDifferent(Individual * ind0, Individual * ind1, Individual * ind2, Individual * ind3);
};

#endif //MSCNProblem_DIFFEVOL_H
