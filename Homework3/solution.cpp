#include "solution.h"

#include <utility>

std::vector<std::vector<long double>> solution::mDistances;
short solution::sChromosome;

void initSolutionClass(std::vector<std::vector<long double>>m_distances){
    solution::mDistances = m_distances;
    solution::sChromosome = m_distances.size();
}

short solution::getChromosomeSize() {
    return solution::sChromosome;
}

std::vector<short> *solution::getChromosome() {
    return &this->chromosome;
}

long double solution::getDistance(short node1, short node2) {
    return solution::mDistances[node1][node2];
}

void solution::assignRndChromosome() {
    short size = solution::sChromosome;
    std::vector<short> rndValues;

    for(short i = 0; i<size;++i){
        chromosome.push_back(i);
        rndValues.push_back(randomTool::genRandomNumBase10(1000));
    }

    for(int i = 0 ; i<size-1;++i){
        for(int j = i+1;j<size;++j){
            if(rndValues[i]<rndValues[j]){
                std::swap(rndValues[i],rndValues[j]);
                std::swap(chromosome[i],chromosome[j]);
            }
        }
    }
}

short &solution::operator[](short index) {
    return chromosome[index];
}

void solution::mutate(short nMutations) {

    short pos1 = randomTool::genRandomNumBase10(sChromosome),pos2;
    do{
        pos2 = randomTool::genRandomNumBase10(sChromosome);
    }while(pos1 == pos2);

        if(randomTool::genRandomBit()){
            std::swap(chromosome[pos1],chromosome[pos2]);
        }else {
            if(pos2 > pos1)std::swap(pos1,pos2);
            while(pos1-pos2>1){
                std::swap(chromosome[pos1],chromosome[pos2]);
                pos1--;
                pos2++;
            }
        }
}

long double solution::evaluate() {
    eval_value = 0;
    for(int i = 0 ; i< sChromosome-1;++i){
        eval_value += solution::getDistance(chromosome[i],chromosome[i+1]);
    }
    return eval_value + solution::getDistance(chromosome[0], chromosome[sChromosome-1]);
}

long double solution::getEval() {
    return eval_value;
}

double solution::getFitness() {
    return fitness;
}

short solution::findNode(short node) {
    bool found = false;
    short i = 0;
    do{
        if(chromosome[i] == node)found = true;
        else ++i;
    }while(!found);

    return i;
}

void solution::crossover(solution& cx1, solution& cx2) {
    short crossover_size = randomTool::genRandomNumBase10(sChromosome); /// configure here the size of exchanged information between chromosomes
    short pos1 = randomTool::genRandomNumBase10(sChromosome-crossover_size);
    auto pos2 = short(pos1 + crossover_size);

    solution cx2_copy = cx2;

    for(short i = pos1; i<=pos2; ++i){
        std::swap(cx2.chromosome[cx2.findNode(cx1[i])],cx2.chromosome[i]);
    }

    for(short i = pos1; i<=pos2; ++i){
        std::swap(cx1.chromosome[cx1.findNode(cx2_copy[i])],cx1.chromosome[i]);
    }

}

solution solution::genRndSolution() {
    solution A;
    A.assignRndChromosome();
    return A;
}

void solution::setFitness(double value) {
    fitness = value;
}

bool solution::operator<(const solution &x) const {
    if (this->eval_value < x.eval_value) return true;
    return false;
}

bool solution::operator>(const solution &x) const {
    if (this->eval_value > x.eval_value) return true;
    return false;
}

float solution::checkMatching(std::vector<short> correctSol) {
    short count=0;
    for(int i = 0;i<sChromosome;++i){
        if(chromosome[i] == correctSol[i])count++;
    }
    return count/(sChromosome*1.0);
}

float solution::checkMatching(long double distance) {

    return distance/eval_value;
}