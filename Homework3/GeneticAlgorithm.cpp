#include "GeneticAlgorithm.h"

#include <utility>
long double GeneticAlgorithm::distance;
GeneticAlgorithm::GeneticAlgorithm(long double optimalLen,std::vector<std::vector<long double>> matrix, short s_population, short n_generations,
                                   short m_mutations, float crossover_rate,float mutation_rate) {
    initRandomClass();
    initSolutionClass(matrix);
    sPopulation = s_population;
    nGenerations = n_generations;
    mMutations = m_mutations;
    crossoverRate = crossover_rate;
    mutationRate = mutation_rate;
    for(int i = 0;i<sPopulation;++i){
        population.push_back(solution::genRndSolution());
    }
    distance = optimalLen;
    new_results.push_back(0);
}



void GeneticAlgorithm::mutatePopulation() {
    auto nPopulation = short(mutationRate * float(sPopulation));
    std::vector<short> rndValues;
    for(int i = 0; i < sPopulation ; ++i){
        rndValues.push_back(randomTool::genRandomNumBase10(1000));
    }
    for(int i = 0;i<sPopulation-1;++i){
        for(int j = i+1;j<sPopulation;++j){
            if(rndValues[i]<rndValues[j]){
                std::swap(rndValues[i],rndValues[j]);
                std::swap(population[i],population[j]);
            }
        }
    }
    for(int i = 0; i < nPopulation;++i){
        population[i].mutate(mMutations);
    }

}

void GeneticAlgorithm::crossoverPopulation() {
    auto nPopulation = short(crossoverRate * float(sPopulation));
    std::vector<short> rndValues;
    for(int i = 0; i < sPopulation ; ++i){
        rndValues.push_back(randomTool::genRandomNumBase10(1000));
    }
    for(int i = 0;i<sPopulation-1;++i){
        for(int j = i+1;j<sPopulation;++j){
            if(rndValues[i]<rndValues[j]){
                std::swap(rndValues[i],rndValues[j]);
                std::swap(population[i],population[j]);
            }
        }
    }
    for(int i = 0; i < nPopulation - 1;i+=2){
        solution::crossover(population[i],population[i+1]);
    }

    if(nPopulation%2){
        if(randomTool::genRandomBit()){
            solution::crossover(population[nPopulation-1],population[nPopulation-2]);
        }
    }

}

long double fabs(long double lhs,long double rhs){
    long double result = lhs - rhs;
    if(result < 0)return  - result;
    return result;
}

void GeneticAlgorithm::evaluatePopulation() {
    long double fitness,maxx=-1,minn=999999;
     for(int i = 0; i<sPopulation ;++i){
        fitness = population[i].evaluate();
        if(fitness > maxx)maxx=fitness;
        if(fitness < minn)minn=fitness;
     }

    std::sort(population.begin(),population.end(),std::greater<solution>());
    for(int i = 0;i<sPopulation;++i){
        fitness = (i+1)/(sPopulation*1.03);
        fitness *=2;
        fitness -=1;
        fitness += 0.001;
        fitness = powf(float(fitness),3) + 1;
        fitness/=2;
        fitness = 1.0/(1+ exp(-4.0 * fitness));
        population[i].setFitness(fitness) ;

    }
}

solution GeneticAlgorithm::getBestSol() {
    solution best_sol = population[0];
    for(int i = 1 ;i<population.size();++i){
        if(population[i] > best_sol){
            best_sol = population[i];
        }
    }

    return best_sol;
}

void GeneticAlgorithm::printPopulation(short iteration) {
    solution bestSol = this->getBestSol();
    std::cout<<std::fixed;
    std::cout.precision(2);
    std::cout<<"Iteration : "<<iteration<<" Eval value : "<<bestSol.getEval()<<" Optimal length : "<<distance<<" Best value : { ";
    std::vector<short> chrom = *bestSol.getChromosome();
    for(auto x : chrom){
        std::cout<<x<<" ";
    }
    std::cout<<"}\n";
}

bool tournament(long double fitness1,long double fitness2){
    if(randomTool::genRandomNumBase10(100)<5)return true;
    if(fitness1>fitness2)return true;
    return false;

}
void GeneticAlgorithm::selectPopulation() {
    std::vector<solution> tournament_population,new_population;
    std::vector<solution> population_copy = population;
    int tournament_size = 200;
    int j;
    bool winner;
    for(int i = 0;i<sPopulation;++i){
        population.clear();
        for(int i = 0; i<tournament_size;++i){
            population.push_back(population_copy[randomTool::genRandomNumBase10(sPopulation)]);
        }
        while(population.size()!=1){
            for(int j = 0; j<population.size()-1;j+=2) {
                winner = tournament(population[j].getFitness(), population[j + 1].getFitness());
                if (winner)tournament_population.push_back(population[j]);
                else tournament_population.push_back(population[j + 1]);
            }

            if(population.size()%2){
                winner = tournament(population[population.size()-1].getFitness(),population[population.size()-2].getFitness());
                if(winner)tournament_population.push_back(population[population.size()-1]);
                else tournament_population.push_back(population[population.size()-2]);
            }

            population = tournament_population;
            tournament_population.clear();
        }

        new_population.push_back(population[0]);
        population = population_copy;
    }

    population = new_population;
}

void GeneticAlgorithm::heat() {
    if(mutationRate < 0.2 and randomTool::genRandomBit()) mutationRate +=0.01;
}

void GeneticAlgorithm::cool() {
    mutationRate = 0.10;
}

long double GeneticAlgorithm::run() {
    for(int i = 1; i <= nGenerations ; ++i){
        evaluatePopulation();
        selectPopulation();
        mutatePopulation();
        crossoverPopulation();
        printPopulation(i);
    }
    return getBestSol().getEval();
   // std::cout<<getBestSol().getEval()<<" "<<distance<<"\n";
}