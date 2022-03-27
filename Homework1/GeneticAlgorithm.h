#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <math.h>

class GeneticAlgorithm{
private:
    std::mt19937_64 g_randomGenerator;
    int dimensions,precision,l,L,iterations,num_of_bits,type;
    long double a,b;
    std::vector<std::vector<bool>> neighbours;
    std::vector<long double> results;
    double temperature;
    long double best_score,new_score;
    std::vector<bool> best_solution;
    int function;
public:
    /*
     * function : 1-DeJong 2-Schwefel 3-Rastrigin 4-Michalewicz
     * type : 1-FI 2-BI 3-SA
     */
     std::vector<bool> generate_random_number();
     void generate_random_solution(std::vector<bool>& solution);
    static unsigned long long int binary2dec(std::vector<bool> bin_num);
     long double dec2interval(unsigned long long int num);
     std::vector<long double> chromosome2double(std::vector<bool> solution);
     long double evaluate_solution(std::vector<bool> candidate);
     void print_solution(std::vector<bool> candidate);

    GeneticAlgorithm(int function,int type,int dimension);
    double run();
    void generate_neighbours(std::vector<bool> chromosome);
    void coolTemp();
};
