#include "GeneticAlgorithm.h"

long double absl(long double x, long double y){
    return x-y > 0 ? x-y : y-x;
}

void __M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg)
{
    // https://stackoverflow.com/questions/3692954/add-custom-messages-in-assert/3692961
    if (!expr)
    {
        std::cerr << "Assert failed:\t" << msg << "\n"
                  << "Expected:\t" << expr_str << "\n"
                  << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}

GeneticAlgorithm::GeneticAlgorithm(const std::string& function_name,short sPopulation,
                                   short nGenerations,short precision,short dimensions,
                                   float mutation_rate,float crossover_rate,float accept_rate,
                                   short method,short crossover_num) {

    this->sPopulation = sPopulation;
    this->nGenerations = nGenerations;
    this->precision = precision;
    this->mutation_rate = mutation_rate;
    this->crossover_rate = crossover_rate;
    this->accept_rate = accept_rate;
    this->method = method;
    this->crossover_num=crossover_num;

    if(function_name == "dejong")function_num = 1;
    else if(function_name == "schwefel")function_num = 2;
    else if(function_name == "rastrigin")function_num = 3;
    else if(function_name == "michalewicz")function_num = 4;
    else if(function_name == "geneticalg")function_num = 5;
    else function_num = 0;
    M_Assert(function_num!=0,"Function is not correct !");

    double a,b;

    switch (function_num) {
        case 1:a = -5.12;b = 5.12;
            break;
        case 2:a = -500; b = 500;
            break;
        case 3:a = -5.12; b = 5.12;
            break;
        case 4:a = 0; b = M_PI;
            break;
        case 5:a = 0.01; b = 1;
            break;
    }
    this->a=a;
    this->b=b;
    this->dimension=dimension;
    randomTool::init();
    solution::initSolutionClass(precision,a,b,dimensions,function_num);
}

void GeneticAlgorithm::genRndPopulation() {
    this->population.clear();
    for(int i=0;i<sPopulation;++i){
        population.push_back(solution::genRndSolution());
    }
}

void GeneticAlgorithm::mutatePopulation() {
    auto mutate_value = short(this->mutation_rate * 100);
    std::pair<bool,solution> offspring;
    for(int i=0;i<sPopulation;++i){
        offspring = this->population[i].mutate(mutate_value);
        if(offspring.first){
            if(method == 1 or method == 3)population.push_back(offspring.second);
            else population[i]=offspring.second;
        }
    }
}

void GeneticAlgorithm::crossoverPopulation() {
    std::vector<float> ran_prob;
    ran_prob.clear();

    for(int i=0;i<sPopulation;++i){
        ran_prob.push_back(float(randomTool::genRandomNumBase10(100) / 100.00));
    }

    auto crossover_value = short(this->crossover_rate * sPopulation);

    for(int i=0;i<sPopulation-1;++i){
        for(int j=i+1;j<sPopulation;++j){
            if(ran_prob[j]<ran_prob[i]){
                std::swap(this->population[j],this->population[i]);
            }
        }
    }

    std::pair<solution,solution> offsprings;

    for(int i=0;i<crossover_value/2;i=i+2){

        offsprings = solution::crossover(this->population[i],this->population[i+1]);
        for(int j=1;j<crossover_num;++j){
            offsprings = solution::crossover(offsprings.first,offsprings.second);
        }
        if(method == 2 or method == 3){
            this->population.push_back(offsprings.first);
            this->population.push_back(offsprings.second);
        }else {
            this->population[i]=offsprings.first;
            this->population[i+1]=offsprings.second;
        }

    }

    if(crossover_value % 2){
        if(randomTool::genRandomBit()){
            offsprings = solution::crossover(this->population[crossover_value - 1],this->population[crossover_value]);
            for(int j=1;j<crossover_num;++j){
                offsprings = solution::crossover(offsprings.first,offsprings.second);
            }
            if(method == 2 or method == 3){
                this->population.push_back(offsprings.first);
                this->population.push_back(offsprings.second);
            }else {
                this->population[crossover_value-1]=offsprings.first;
                this->population[crossover_value]=offsprings.second;
            }
        }
    }
}

std::vector<solution> GeneticAlgorithm::selectPopulation(std::vector<solution> population,int sPopulation) {
    std::vector<solution> new_population;
    new_population.clear();

    float ran_num;
    bool found ;

    std::sort(population.begin(),population.end(),std::greater<solution>());

   for(int i = 0; i < sPopulation ; ++i){
       ran_num = float(randomTool::genRandomNumBase10(99) / 100.00) ;
       if(ran_num < 0) ran_num = -ran_num;
       ran_num += 0.01;
       found = false;
       int j=0;
       while (!found){
           if(ran_num < population[j].getFitnessValue()){
               found = true;
               new_population.push_back(population[j]);
           }
           ++j;
           if(j == population.size()){
               int ran_index = randomTool::genRandomNumBase10(population.size());
               new_population.push_back(population[ran_index]);
               found = true;
           };
       }
   }

    return new_population;
}

void GeneticAlgorithm::printPopulation(short iteration) {
    solution bestSol = getBestSolution();
    std::cout<<std::fixed;
    std::cout.precision(this->precision);
    std::cout<<"Iteration : "<<iteration<<" Eval value : "<<bestSol.getEvalValue()<<" Best value : { ";
    for(auto x:bestSol.getChromosomeDouble()){
        std::cout<<x<<"  ";
    }
    std::cout<<"}\n";
}

void GeneticAlgorithm::evaluatePopulation() {
    long double maxx=-9999999,minn=9999999, value;
    for(int i=0;i<population.size();++i){
        population[i].evaluate();
        if(function_num == 5) {
            solution::initSolutionClass(precision, a, b, dimension, function_num);
        }
        value = population[i].getEvalValue();

        if(value > maxx) maxx = value;
        if(value < minn) minn = value;
    }



    maxx += 0.000001;
    for(int i=0;i<population.size();++i){
        value = absl(population[i].getEvalValue(), minn) / (absl(maxx,minn) +0.01)  + 0.01;
        value = 1 - value;
        value *= accept_rate;
        if(value < 0.01)population[i].setFitnessValue(0.01);
        else population[i].setFitnessValue(value);
    }
}

solution GeneticAlgorithm::getBestSolution() {
    solution best_sol = population[0];
    for(int i = 1 ;i<population.size();++i){
        if(population[i] > best_sol){
            best_sol = population[i];
        }
    }

    return best_sol;
}

long double  GeneticAlgorithm::run() {
    this->genRndPopulation();
    for(short i=1 ; i<=nGenerations ; ++i ){

        this->mutatePopulation();
        this->crossoverPopulation();
        this->mutatePopulation();
        this->evaluatePopulation();

        this->population = this->selectPopulation(population,sPopulation);
        this->printPopulation(i);

    }

    return this->getBestSolution().getEvalValue();
}