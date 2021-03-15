#ifndef MSCNProblem_MSCNPROBLEM_H
#define MSCNProblem_MSCNPROBLEM_H

#include "Table.h"
#include "Matrix.h"
#include <iostream>
#include "ProblemFileReader.h"
#include "ProblemFileWriter.h"
#include "Const.h"
#include "Random.h"
#include "Problem.h"

class MscnProblem : public Problem {
private:
    int d_count;
    int f_count;
    int m_count;
    int s_count;

    Table<double> *sd_tab;  //capacity
    Table<double> *sf_tab;
    Table<double> *sm_tab;
    Table<double> *ss_tab;

    Matrix<double> *cd_mat;  //cost
    Matrix<double> *cf_mat;
    Matrix<double> *cm_mat;

    Table<double> *ud_tab;   //unitary cost
    Table<double> *uf_tab;
    Table<double> *um_tab;

    Table<double> *ps_income_tab;

    Matrix<double> *xd;   //amount
    Matrix<double> *xf;
    Matrix<double> *xm;

    Matrix<double> *xd_max;
    Matrix<double> *xd_min;
    Matrix<double> *xf_max;
    Matrix<double> *xf_min;
    Matrix<double> *xm_max;
    Matrix<double> *xm_min;

    Table<double> *solution;

public:
    MscnProblem();
    ~MscnProblem();

    bool setD_count(int new_count);
    bool setF_count(int new_count);
    bool setM_count(int new_count);
    bool setS_count(int new_count);

    bool open(const char* file_name);
    bool save(const char* file_name);
    bool saveSolution(const char* file_name);
    void print();
    double getQuality();
    bool initSolution(Table<double>* solution);
    void qualitySatisfier();
    void generateInstance(Random* ra);
    Table<double>* getSolution();
    void setSolution(Table<double> *table);
};

#endif //MSCNProblem_MSCNPROBLEM_H
