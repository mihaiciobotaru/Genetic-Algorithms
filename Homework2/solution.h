#ifndef GENETICHELLOWORLD_SOLUTION_H
#define GENETICHELLOWORLD_SOLUTION_H

#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

class randomTool{
    static std::mt19937_64 g_randomGenerator;
    friend class solution;
    static std::vector<bool> genRandomNumBase2(int num_of_bits);
public:
    static void init();
    static int genRandomNumBase10(int moduloX);
    static bool genRandomBit();


};

class solution{
private:
    std::vector<bool> chromosome;
    std::vector<long double> chromosomeD;
    long double eval_value;
    float fitness;
    static short lChromosome;
    static short dimensions;
    static short function_num;
    static double a,b;
    friend class randomTool;

    static unsigned long long int binary2dec(const std::vector<bool>& bin_num);
    static long double dec2interval(unsigned long long int num);
    static std::vector<long double> binary2chromosomeD(std::vector<bool> bin_num);
public:
    [[nodiscard]] std::pair<bool,solution> mutate(short mutation_rate) const ;
    static std::pair<solution,solution> crossover(solution cx1,solution cx2);
    static std::pair<solution,solution> crossover(const std::pair<solution,solution>&);
    static solution genRndSolution();
    static void initSolutionClass(short precision,double a,double b,short dimensions,short function_num);

    void evaluate();
    long double getEvalValue();
    float getFitnessValue() const;
    void setFitnessValue(float fitness);
    std::vector<long double> getChromosomeDouble();
    void print2b();

    bool operator<(const solution &x) const;
    bool operator>(const solution &x) const;

    void sync();
};

#endif //GENETICHELLOWORLD_SOLUTION_H
