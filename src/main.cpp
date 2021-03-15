#include "../include/MscnProblem.h"
#include "../include/RandomSearch.h"
#include "../include/DiffEvol.h"
#include "../include/Timer.h"
#include <thread>

void loadingTest() {
    ProblemFileReader<double> fr("../txt/openTest.txt");
    Table<double> *tab = new Table<double>(10);
    Table<double> *tab1 = new Table<double>(7);
    Matrix<double> *mat = new Matrix<double>(3,3);
    fr.fillTable(tab);
    fr.fillTable(tab1);
    fr.fillMatrix(mat);

    tab->print();
    tab1->print();
    mat->print();
    delete tab;
    delete tab1;
    delete mat;
}

bool exerciseTest() {
    int size = 100;
    Table<double>* solution = new Table<double>(100);

    for (int i = 0; i < size; i++) {
        solution->set(i, 1);
    }

    MscnProblem prob;

    if (!prob.open("../txt/problem.txt"))
        return false;

    prob.save("../txt/solution.txt");
    std::cout<<"\nquality: "<<prob.getQuality()<<"\n";
    prob.print();

    return true;
}

void testRandomSearch() {
    MscnProblem* problem = new MscnProblem();
    problem->open("../txt/problem.txt");
    RandomSearch *randS = new RandomSearch(problem);
    Timer timer;
    timer.time_start();

    std::cout<<randS->compute();
    std::cout<<"\ntime: "<<timer.time_stop();

    problem->initSolution(problem->getSolution());
    problem->save("../txt/randomProblem.txt");
    problem->saveSolution("../txt/randomSolution.txt");

    delete randS;
    delete problem;
}

bool testDiffEvol() {
    MscnProblem *problem = new MscnProblem();
    Random* rand = new Random(time(NULL));
    problem->open("../txt/problem.txt");

    bool correct_param = true;
    DiffEvol *dv = new DiffEvol(problem,rand,POPULATION,0.5,0.5,correct_param);

    if (!correct_param) {
        delete dv;
        delete problem;
        return false;
    }

    Timer timer;
    timer.time_start();
    std::cout<<dv->compute();

    std::cout<<"\ntime: "<<timer.time_stop()<<"\n";

    problem->initSolution(problem->getSolution());
    problem->save("../txt/randomProblem.txt");
    problem->saveSolution("../txt/diffSolution.txt");

    delete dv;
    delete problem;
    return true;
}

bool compareTest() {
    MscnProblem *problem = new MscnProblem();
    Random* rand = new Random(time(NULL));
    problem->open("../txt/problem.txt");

    bool correct_param = true;
    DiffEvol *dv = new DiffEvol(problem,rand,POPULATION,0.5,0.5,correct_param);

    if (!correct_param) {
        delete dv;
        delete problem;
        return false;
    }

    Timer timer;
    timer.time_start();

    std::cout<<"diffEvol: "<<dv->compute()<<"\n";
    std::cout<<"\ntime: "<<timer.time_stop()<<"\n";

    problem->initSolution(problem->getSolution());
    problem->save("../txt/randomProblem.txt");
    problem->saveSolution("../txt/diffSolution.txt");

    RandomSearch *randS = new RandomSearch(problem);

    timer.time_start();

    std::cout<<randS->compute();
    std::cout<<"\n time_random: "<<timer.time_stop();

    problem->initSolution(problem->getSolution());
    problem->save("../txt/randomProblem.txt");
    problem->saveSolution("../txt/randomSolution.txt");

    delete randS;
    delete dv;
    delete problem;
    return true;
}

int main() {
    //loadingTest();
    //std::cout<<"functionality: "<<exerciseTest();
    //testRandomSearch();
    //compareTest();
    std::thread thread(&testDiffEvol);
    thread.join();

    return 0;
}