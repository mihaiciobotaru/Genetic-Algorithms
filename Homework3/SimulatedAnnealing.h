#ifndef TRAVELLING_SALESMAN_GENETIC_ALGORITHM_SIMULATEDANNEALING_H
#define TRAVELLING_SALESMAN_GENETIC_ALGORITHM_SIMULATEDANNEALING_H
#include "solution.h"
#include <cmath>
#include <algorithm>

class SimulatedAnnealing{
private:
    static long double distance;
    int nIterations;

public:
    SimulatedAnnealing(long double optimalLen,std::vector<std::vector<long double>> matrix,short n_iterations);
    long double run();
};

#endif //TRAVELLING_SALESMAN_GENETIC_ALGORITHM_SIMULATEDANNEALING_H
