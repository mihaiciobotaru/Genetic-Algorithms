#ifndef TRAVELLING_SALESMAN_GENETIC_ALGORITHM_PARSER_H
#define TRAVELLING_SALESMAN_GENETIC_ALGORITHM_PARSER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define PATH "../Instances/"

struct position{
    long double x,y;
    bool operator==(const position& rhs);
};

std::pair<long double, std::vector<position>> getInstance(const std::string& path);

#endif //TRAVELLING_SALESMAN_GENETIC_ALGORITHM_PARSER_H
