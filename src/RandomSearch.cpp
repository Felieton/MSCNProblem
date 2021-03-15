#include "../include/RandomSearch.h"
#include "../include/Const.h"
#include "../include/Timer.h"

RandomSearch::RandomSearch() {
    problem = nullptr;
}

RandomSearch::RandomSearch(Problem* prob) {
    problem = prob;
}

RandomSearch::~RandomSearch() {
}

double RandomSearch::compute() {
    Random *ra = new Random(time(NULL));
    Table<double> *solution = new Table<double>(problem->getSolution()->getSize());

    double best_quality = DBL_MIN;
    double quality = 0;

    Timer timer;
    timer.time_start();

    while (timer.time_stop() < STOP) {
        ra->randFillTable(solution, 0, X_MAX);

        problem->initSolution(solution);
        quality = problem->getQuality();

        if (quality > best_quality) {
            std::cout << best_quality << std::endl;
            best_quality = quality;

            problem->setSolution(solution);
        }
    }

    delete solution;
    delete ra;

    return best_quality;
}

