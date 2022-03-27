#ifndef GENETICHELLOWORLD_GENETICALGORITHM_H
#define GENETICHELLOWORLD_GENETICALGORITHM_H

#include "solution.h"
#include <cmath>
#include <iomanip>
#ifndef NDEBUG
#   define M_Assert(Expr, Msg) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define M_Assert(Expr, Msg) ;
#endif

// https://stackoverflow.com/questions/3692954/add-custom-messages-in-assert/3692961


class GeneticAlgorithm{
private:
    std::vector<solution> population;

    short function_num;
    short sPopulation;
    short nGenerations;
    short precision;
    float mutation_rate;
    float crossover_rate;
    float accept_rate;
    float a,b,dimension;
    short method;
    short crossover_num;

    void genRndPopulation();
    void evaluatePopulation(); ///not implemented
    void printPopulation(short iteration);
    static std::vector<solution> selectPopulation(std::vector<solution> population,int sPopulation);
    void mutatePopulation();
    void crossoverPopulation();

    solution getBestSolution();

public:
    GeneticAlgorithm(const std::string& function_name,short sPopulation,
                     short nGenerations,short precision,short dimensions,
                     float mutation_rate,float crossover_rate,float  accept_rate,
                     short method,short crossover_num); ///not finished
    long double run();
};

#endif //GENETICHELLOWORLD_GENETICALGORITHM_H
