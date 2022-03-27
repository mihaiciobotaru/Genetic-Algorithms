#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int function, int type, int dimension) {
    this->type = type;
    this->function = function;
    dimensions = dimension;
    precision = 5;
    iterations = 300;
    temperature = 100;
    switch (function) {
        case 1:a = -5.12; b = 5.12;
        break;
        case 2:a = -500; b = 500;
        break;
        case 3:a = -5.12; b = 5.12;
        break;
        case 4:a = 0; b = M_PI;
        break;
    }
    results.clear();
    l = int(log(pow(10,precision)*(b-a))) + 1;
    L = l*dimensions;
    num_of_bits=l;

    std::mt19937_64 initializer;
    initializer.seed(static_cast<unsigned long long int>(std::chrono::high_resolution_clock::now().time_since_epoch().count() ) );
    initializer.discard(10000);
    g_randomGenerator.seed(initializer());
}

std::vector<bool> GeneticAlgorithm::generate_random_number(){
    std::vector<bool> random_number;
    random_number.reserve(this->num_of_bits);
    for(int i=0;i<this->num_of_bits;++i){
        random_number.push_back(g_randomGenerator()%2);
    }
    return random_number;
}
void GeneticAlgorithm::generate_random_solution(std::vector<bool>& solution){
    std::vector<bool> temp;
    for(int i=0;i<dimensions;i++){
        temp = generate_random_number();
        for(auto gene : temp){
            solution.push_back(gene);
        }
    }
}
unsigned long long int GeneticAlgorithm::binary2dec(std::vector<bool> bin_num){
    unsigned long long int sum=0,pow=1;
    for(auto x:bin_num){
        sum+=x*pow;
        pow*=2;
    }
    return sum;
}
long double GeneticAlgorithm::dec2interval(unsigned long long int num){
    long double result = num/((pow(2,l)-1));
    result *= double(b-a);
    result += a;

    return result;
}
std::vector<long double> GeneticAlgorithm::chromosome2double(std::vector<bool> solution){
    std::vector<bool> temp;
    std::vector<long double> result;
    for(int i=0;i<solution.size();++i){
        if(i%this->num_of_bits==0 and i!=0){
            result.push_back(dec2interval(binary2dec(temp)));
            temp.clear();
            temp.push_back(solution[i]);
        }else{
            temp.push_back(solution[i]);
        }
    }
    result.push_back(dec2interval(binary2dec(temp)));
    return result;
}
void GeneticAlgorithm::generate_neighbours(std::vector<bool> chromosome){
    neighbours.clear();
    std::vector<bool> chromosome_copy;
    for(int i=0;i<chromosome.size() - 1 ;++i){
        chromosome_copy = chromosome;
        chromosome_copy[chromosome.size() - i - 1] = 1- chromosome_copy[chromosome.size() - i - 1];
        chromosome_copy[chromosome.size() - i - 2] = 1- chromosome_copy[chromosome.size() - i - 2];
        neighbours.push_back(chromosome_copy);
    }
}
long double GeneticAlgorithm::evaluate_solution(std::vector<bool> candidate){
    long double sum=0;
    std::vector<long double> num = chromosome2double(candidate);
    switch (this->function) {
        case 1:
            for(auto x: num){
                sum += x*x;
            }

            return sum;
        case 2:
            for(auto x: num){
                sum += -x* sin(sqrt(abs(x)));
            }

            return sum;
        case 3:
            for(auto x: num){
                sum += x*x - 10*cos(2*x*M_PI);
            }

            return 10* dimensions + sum;
        case 4:
            long double x;
            int m=10;
            for(int i=0;i<num.size();++i){
                x = num[i];
                sum += sin(x) * pow(sin(((i+1)*x*x)/M_PI),2*m);
            }

            return -sum;
    }

}
void GeneticAlgorithm::print_solution(std::vector<bool> candidate){
    std::vector<long double> num = chromosome2double(candidate);
    std::cout<<"{ ";
    std::cout.precision(precision);
    for(auto x:num)std::cout<<std::fixed<<x<<" ";
    std::cout<<"}";
}
void GeneticAlgorithm::coolTemp(){
    temperature*=0.995;
}

double GeneticAlgorithm::run() {
    generate_random_solution(this->best_solution);
    best_score = GeneticAlgorithm::evaluate_solution(best_solution);
    for(int i=0;i<iterations;++i){
        //std::cout<<"The best value so far is : "<<best_score<<" ,the solution is : ";
        //print_solution(best_solution);
        //std::cout<<" , iteration "<<i+1<<"\n";

        generate_neighbours(best_solution);

        for(auto candidate:neighbours){
            new_score = evaluate_solution(candidate);
            if(new_score< best_score){
                best_score = new_score;
                best_solution = candidate;
                if(type == 1)break;
            }else if(exp((best_score-new_score)/temperature) && type==3){
                best_score = new_score;
                best_solution = candidate;
                coolTemp();
            }

        }
        results.push_back(best_score);
    }
    return best_score;
}
