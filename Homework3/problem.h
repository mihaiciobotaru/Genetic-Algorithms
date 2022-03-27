#ifndef TRAVELLING_SALESMAN_GENETIC_ALGORITHM_PROBLEM_H
#define TRAVELLING_SALESMAN_GENETIC_ALGORITHM_PROBLEM_H
#include <vector>
#include "randomTool.h"
#include <set>
#include <cmath>
#include "parser.h"

class problem{
private:
    long double optimalLength;
    std::vector<position> positions;
    std::vector<std::vector<long double>> distances;
public:
    problem(int nCities);
    problem(std::string path,int cities);
    std::vector<std::vector<long double>> getDistances();
    long double getOptimalLen();
    position& operator[](int index);
};

#endif //TRAVELLING_SALESMAN_GENETIC_ALGORITHM_PROBLEM_H
