#ifndef TSPGA_GENETICALGORITHM_H
#define TSPGA_GENETICALGORITHM_H
#include "solution.h"
#include <cmath>
#include <algorithm>
/*
 * http://www.iaeng.org/publication/WCE2011/WCE2011_pp1134-1139.pdf Genetic algorithm performance with different selection strategies in solving TSP
 *
 */

class GeneticAlgorithm{
private:
    static long double distance;
    std::vector<solution> population;
    short sPopulation,nGenerations;
    short mMutations;
    float crossoverRate;
    float mutationRate;
    long double current_best,last_best;
    std::vector<int> new_results;

public:

    void heat();
    void cool();

    GeneticAlgorithm(long double optimalLen,std::vector<std::vector<long double>> matrix,short s_population,short n_generations,short m_mutations,float crossover_rate,float mutation_rate);
    void crossoverPopulation();
    void mutatePopulation();
    void selectPopulation();
    void evaluatePopulation();
    void printPopulation(short iteration);
    solution getBestSol();
    void coolMutations();
    long double run();
};

#endif //TSPGA_GENETICALGORITHM_H
