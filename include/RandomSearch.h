#ifndef MSCNProblem_RANDOMSEARCH_H
#define MSCNProblem_RANDOMSEARCH_H

#include "Table.h"
#include "Random.h"
#include <iostream>
#include <time.h>
#include "MscnProblem.h"
#include "Optimizer.h"


class RandomSearch : public Optimizer {
private:
    Problem* problem;
public:
    RandomSearch();
    RandomSearch(Problem* prob);
    ~RandomSearch();
    double compute() override;

};


#endif //MSCNProblem_RANDOMSEARCH_H
