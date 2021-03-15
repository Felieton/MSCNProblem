#ifndef MSCNProblem_PROBLEM_H
#define MSCNProblem_PROBLEM_H

class Problem {
public:
    virtual Table<double>* getSolution() = 0;
    virtual void setSolution(Table<double> *table) = 0;
    virtual double getQuality() = 0;
    virtual bool initSolution(Table<double>* solution) = 0;
};

#endif //MSCNProblem_PROBLEM_H
