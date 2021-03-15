#include "../include/DiffEvol.h"
#include "../include/Timer.h"

DiffEvol::DiffEvol() {
    problem = nullptr;
    population = nullptr;
    ran = nullptr;
    cross_prob = 0;
    diff_weight = 0;
}

DiffEvol::DiffEvol(Problem *nproblem, Random *nran, int size_of_population,
        double ncross_prob, double ndiff_weight, bool &correct_param) {
    if (ncross_prob < 0 || ncross_prob > 1 || ndiff_weight < 0 || ndiff_weight > 1) {
        correct_param = false;
    }

    cross_prob = ncross_prob;
    diff_weight = ndiff_weight;

    problem = nproblem;
    population = new Table<Individual*>(size_of_population);
    ran = nran;
}

DiffEvol::~DiffEvol() {
    delete population;
    delete ran;
}

double DiffEvol::compute() {
    Individual *ind;
    Individual *base;
    Individual *ind0;
    Individual *ind1;
    Individual *ind_new = new Individual;

    generatePopulation();
    Timer timer;
    timer.time_start();

    while (timer.time_stop() < STOP) {
        for (int i = 0; i < population->getSize(); i++) {
            ind = population->get(i);
            do {
                base = getRandomInd();
                ind0 = getRandomInd();
                ind1 = getRandomInd();
            } while (!indAreDifferent(ind, base, ind0, ind1));

            for (int i_gene = 0; i_gene < problem->getSolution()->getSize(); i_gene++) {
                if (ran->randomDouble(0, 1) < cross_prob) {
                    double new_gene =
                            base->getGene(i_gene) + (diff_weight * (ind0->getGene(i_gene) - ind1->getGene(i_gene)));

                    if (new_gene < X_MAX)  //gene can be out of field
                        ind_new->getGenotype()->set(i_gene, new_gene);
                    else  //back to ind's gene
                        ind_new->getGenotype()->set(i_gene, ind->getGenotype()->get(i_gene));

                } else
                    ind_new->getGenotype()->set(i_gene, ind->getGenotype()->get(i_gene));

                if (ind_new->getFitness(problem) >= ind->getFitness(problem))
                    ind = ind_new;

            }
        }
    }

    double best_sol = -DBL_MAX;
    double sol;

    for (int i = 0; i < population->getSize(); i++) {
        sol = population->get(i)->getFitness(problem);
        if (sol > best_sol) {
            problem->setSolution(population->get(i)->getGenotype());
            best_sol = sol;
        }
    }

    return best_sol;
}

bool DiffEvol::generatePopulation() {
    int ind_size = problem->getSolution()->getSize();
    Individual *ind;

    for (int i = 0; i < population->getSize(); i++) {
        ind = new Individual(ran, ind_size);

        population ->set(i, ind);
    }

    return true;
}

Individual* DiffEvol::getRandomInd() {
    return population->get(ran->randomInteger(0,population->getSize()));
}

bool DiffEvol::indAreDifferent(Individual *ind0, Individual *ind1, Individual *ind2, Individual *ind3) {
    return !(ind0 == ind1 || ind0 == ind2 || ind0 == ind3 || ind1 == ind2 || ind1 == ind3 || ind2 == ind3);
}