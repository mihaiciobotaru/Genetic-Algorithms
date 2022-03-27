#include "SimulatedAnnealing.h"

long double SimulatedAnnealing::distance;
SimulatedAnnealing::SimulatedAnnealing(long double optimalLen, std::vector<std::vector<long double>> matrix,
                                       short n_iterations) {
    initRandomClass();
    initSolutionClass(matrix);
    nIterations = n_iterations;
    distance = optimalLen;
}


double min(double lhs,double rhs){
    if(lhs < rhs)return lhs;
    return rhs;
}

long double SimulatedAnnealing::run() {
    solution current_solution = solution::genRndSolution();
    solution candidate;
    long double current_eval = current_solution.evaluate();
    long double candidate_eval;

    long double temperature = 2500, t, metropolis, diff;

    bool exit;

    for (int i = 1; i <= nIterations; ++i) {
        exit = false;
        for (int j = 0; j < 200 && !exit; ++j) {
            candidate = current_solution;
            candidate.mutate(3);
            candidate_eval = candidate.evaluate();

            if (candidate_eval <= current_eval) {
                current_solution = candidate;
                current_eval = candidate_eval;
                exit = true;
            } else {
                diff = candidate_eval - current_eval;
                t = temperature -  2*float(i);
                t = min(t,75);
                metropolis = exp(-diff + t);
                if (randomTool::genRandomNumBase10(1000) < metropolis ) {
                    current_solution = candidate;
                    current_eval = candidate_eval;
                    exit = true;
                }
            }
        }
        std::cout<<"Iteration: "<<i<<" Value: "<<current_eval<<"\n";
    }
   // std::cout << current_eval << " " << distance << "\n";
    return current_eval;
}
