#include <iostream>
#include "GeneticAlgorithm.h"
int main(){

    long double temp,max,mean,min,mean_t;
    short iterations=50,dimension;
    long double temp_t;
    std::cout.precision(5);
    std::string function_name;
    GeneticAlgorithm GA("rastrigin",450,450,5,1,0.01,1.00,0.70,1,3);
    temp = GA.run();

    for(int ii=1;ii<=4;++ii){
        if(ii == 1)function_name = "dejong";
        else if(ii == 2)function_name = "schwefel";
        else if(ii == 3)function_name = "rastrigin";
        else if(ii == 4)function_name = "michalewicz";
        for(int i=2 ;i<3;++i){
            switch (i) {
                case 0:dimension = 5; break;
                case 1:dimension = 10; break;
                case 2:dimension = 30; break;
            }
            switch (ii) {
                case 1:std::cout<<"DeJong`s Function "; break;
                case 2:std::cout<<"Schwefel`s Function "; break;
                case 3:std::cout<<"Rastrigin`s Function "; break;
                case 4:std::cout<<"Michalewicz`s Function "; break;
            }
                std::cout<<"Dimension "<<dimension<<"\n";
                max=-99999;mean=0;min=99999;
                mean_t=0;
                for(int k=0;k<iterations;++k){
                    GeneticAlgorithm GA(function_name,450,450,5,dimension,0.01,1.00,0.70,1,3);
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

    return 0;
}