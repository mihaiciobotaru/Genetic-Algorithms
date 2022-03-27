#ifndef TSPGA_solution_H
#define TSPGA_solution_H

#include "randomTool.h"
#include <iostream>
#include <vector>

class solution{
private:
    static std::vector<std::vector<long double>>mDistances;/// a matrix of distance between each city
    static short sChromosome;/// size of Chromosome / number of cities in a chromosome

    std::vector<short> chromosome;/// order of cities
    long double eval_value;
    double fitness;
public:
    short findNode(short node);
    long double evaluate();
    long double getEval();
    double getFitness();
    void setFitness(double value);
    short& operator[](short index);
    std::vector<short>* getChromosome();
    void mutate(short nMutations);
    void assignRndChromosome();
    static long double getDistance(short node1,short node2);
    static void crossover(solution& cx1,solution& cx2);
    static short getChromosomeSize();
    friend void initSolutionClass(std::vector<std::vector<long double>>m_distances);
    static solution genRndSolution();
    float checkMatching(std::vector<short> correctSol);
    float checkMatching(long double distance);
    bool operator<(const solution &x) const;
    bool operator>(const solution &x) const;
};

void initSolutionClass(std::vector<std::vector<long double>>m_distances);

#endif //TSPGA_solution_H
