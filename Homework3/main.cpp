#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"
#include "problem.h"
int main()
{
    std::string path;
    std::cout.precision(5);

    problem prob("gil262",262);

    GeneticAlgorithm GA(prob.getOptimalLen(),prob.getDistances(),200,2000,3,0.50,0.50);
    SimulatedAnnealing SA(prob.getOptimalLen(), prob.getDistances(), 2000);
    GA.run();
    //SA.run();
    return 0;
}
