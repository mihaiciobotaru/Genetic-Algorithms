#include <iostream>
#include "GeneticAlgorithm.h"
int main(){
    long double temp,max,mean,min,dimension,mean_t;
    int iterations=400;
    long double temp_t;
    std::cout.precision(5);

    for(int ii=0;ii<=3;++ii){
        switch (ii) {
            case 0:dimension = 5; break;
            case 1:dimension = 10; break;
            case 2:dimension = 30; break;
            case 3:dimension = 100; break;
        }
        for(int i=1 ;i<=4;++i){
            switch (i) {
                case 1:std::cout<<"DeJong`s Function "; break;
                case 2:std::cout<<"Schwefel`s Function "; break;
                case 3:std::cout<<"Rastrigin`s Function "; break;
                case 4:std::cout<<"Michalewicz`s Function "; break;
            }
            for(int j=1;j<=3;++j){
                switch (j) {
                    case 1:std::cout<<"First Improvement"; break;
                    case 2:std::cout<<"Best Improvement"; break;
                    case 3:std::cout<<"Simulated Annealing"; break;
                }
                std::cout<<" Dimension "<<dimension<<"\n";
                max=-99999;mean=0;min=99999;
                mean_t=0;
                for(int k=0;k<iterations;++k){
                    GeneticAlgorithm GA(i,j,dimension);
                    auto start = std::chrono::high_resolution_clock::now();
                    temp = GA.run();
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                    temp_t = duration.count() / 1000000.00;
                    if(temp>max)max = temp;
                    if(temp<min)min = temp;
                    mean+=temp;

                    mean_t+=temp_t;
                }
                std::cout<<std::fixed<<max<<" "<<mean/iterations<<" "<<min<<" "<< mean_t/iterations<<"\n";
            }
        }
    }

    return 0;
}