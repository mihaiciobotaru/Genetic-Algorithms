#include "solution.h"
#include "GeneticAlgorithm.h"

/// Random Tool Class implementation

std::mt19937_64 randomTool::g_randomGenerator;

void randomTool::init() {
    std::mt19937_64 initializer;
    initializer.seed(static_cast<unsigned long long int>(std::chrono::high_resolution_clock::now().time_since_epoch().count() ) );
    initializer.discard(10000);
    g_randomGenerator.seed(initializer());
}

bool randomTool::genRandomBit() {
    return g_randomGenerator()%2;
}
std::vector<bool> randomTool::genRandomNumBase2(int num_of_bits) {
    std::vector<bool> random_number;
    random_number.reserve(num_of_bits);
    for(int i=0;i<num_of_bits;++i){
        random_number.push_back(g_randomGenerator()%2);
    }

    return random_number;
}

int randomTool::genRandomNumBase10(int moduloX) {
    return abs(int(g_randomGenerator())%moduloX);
}


/// Solution Class Implementation
short solution::lChromosome;
short solution::dimensions;
short solution::function_num;
double solution::a;
double solution::b;

void solution::initSolutionClass(short precisionx, double ax, double bx,short dimensionsx,short function_numx) {
    solution::lChromosome = static_cast<short>((log(pow(10,precisionx)*(bx-ax))) + 1);
    solution::dimensions = dimensionsx;
    solution::function_num = function_numx;
    solution::a=ax;
    solution::b=bx;
}


std::pair<bool,solution> solution::mutate(const short mutation_rate) const {
    short ran_num;
    solution new_solution = *this;
    bool modified = false;

    for(int i=0; i < chromosome.size() ; ++i){
        ran_num = short (randomTool::genRandomNumBase10(100));
        if(ran_num <= mutation_rate){
            new_solution.chromosome[i] = !new_solution.chromosome[i] ;
            modified = true;
        }
    }

    new_solution.sync();
    return {modified,new_solution};
}

std::pair<solution,solution> solution::crossover(solution cx1,solution cx2) {
    int startPos = randomTool::genRandomNumBase10(cx1.chromosome.size());
    int endPos = startPos + randomTool::genRandomNumBase10(cx1.chromosome.size() - startPos);

    for(int i = startPos ; i<=endPos ; ++i){
        std::swap(cx1.chromosome[i],cx2.chromosome[i]);
    }

    cx1.sync();
    cx2.sync();
    return {cx1,cx2};
}

std::pair<solution, solution> solution::crossover(const std::pair<solution, solution>& cx) {
    solution cx1 = cx.first;
    solution cx2 = cx.second;

    return crossover(cx1,cx2);
}


solution solution::genRndSolution() {
    solution new_candidate;
    std::vector<bool> new_chromosome , new_binaryNum;
    new_chromosome.clear();

    for(int i = 0 ; i<dimensions ; ++i){
        new_binaryNum = randomTool::genRandomNumBase2(lChromosome);
        for(int j = 0 ; j<lChromosome ; ++j ){
            new_chromosome.push_back(new_binaryNum[j]);
        }
    }

    new_candidate.chromosome = new_chromosome;
    new_candidate.sync();
    return new_candidate;
}
void solution::evaluate() {
    long double sum=0;
    if(function_num == 1){
        for(auto x: this->chromosomeD){
            sum += x*x;
        }
        eval_value = sum;
    }else if(function_num == 2){
        for(auto x: this->chromosomeD){
            sum += -x* sinl(sqrtl(std::abs(x)));
        }

        eval_value = sum;
    }else if(function_num == 3){
        for(auto x: this->chromosomeD){
            sum += x*x - 10*cosl(2*x*M_PI);
        }

        eval_value = 10* dimensions + sum;
    }else if(function_num == 4){
        long double x;
        int m=10;
        for(int i=0;i<dimensions;++i){
            x = this->chromosomeD[i];
            sum += sinl(x) * powl(sinl(((i+1)*x*x)/M_PI),2*m);
        }
        eval_value = -sum;
    }else {
        short method;
        if(short (chromosomeD[4])%4 == 0 ) method = 0;
        else if(short(chromosomeD[4])%4 == 1) method = 1;
        else if(short(chromosomeD[4]) % 4 == 2) method = 2;
        else method = 3;
        GeneticAlgorithm GAx("rastrigin",60,30,2,5,chromosomeD[1],chromosomeD[2],chromosomeD[3],method,chromosomeD[1]*10);
        long double avg=0;
        for(int i = 0; i < 100;++i){
            avg += GAx.run() ;

        }
        eval_value = avg/100;
    }
}

long double solution::getEvalValue() {
    return eval_value;
}

unsigned long long int solution::binary2dec(const std::vector<bool>& bin_num){

    unsigned long long int sum=0,pow=1;
    for(auto x:bin_num){
        sum+=x*pow;
        pow*=2;
    }
    return sum;
}
long double solution::dec2interval(unsigned long long int num){
    long double result = num/((powl(2,lChromosome)-1));
    result *= double(b-a);
    result += a;

    return result;
}

std::vector<long double> solution::binary2chromosomeD(std::vector<bool> bin_num) {
    std::vector<bool> temp;
    std::vector<long double> result;

    for(int i=0;i<bin_num.size();++i){
        if(i%lChromosome==0 and i!=0){
            result.push_back(dec2interval(binary2dec(temp)));
            temp.clear();
            temp.push_back(bin_num[i]);
        }else{
            temp.push_back(bin_num[i]);
        }
    }
    result.push_back(dec2interval(binary2dec(temp)));
    return result;

}

std::vector<long double> solution::getChromosomeDouble() {
    return chromosomeD;
}

bool solution::operator<(const solution &x) const {
    return (this->fitness < x.fitness);
}

bool solution::operator>(const solution &x) const {
    return (this->fitness > x.fitness);
}

void solution::sync() {
    chromosomeD = binary2chromosomeD(chromosome);
}

void solution::setFitnessValue(float fitnessx) {
    this->fitness = fitnessx;
}

float solution::getFitnessValue() const {
    return this->fitness;
}

void solution::print2b() {
    for(auto x : chromosome){
        std::cout<<x;
    }std::cout<<"\n";
}