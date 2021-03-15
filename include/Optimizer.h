#ifndef MSCNProblem_OPTIMIZER_H
#define MSCNProblem_OPTIMIZER_H

class Optimizer {
private:
    Problem* problem;
public:
    virtual double compute() = 0;
};

#endif //MSCNProblem_OPTIMIZER_H
