#include "problem.h"

long double distance2points(position a,position b){
    return sqrt(pow(a.x-b.x,2)+ pow(a.y-b.y,2));
}

problem::problem(int nCities) {
    initRandomClass();
    bool inserted;
    for (int i = 0; i < nCities; ++i) {
        position new_pos;
        do{
               new_pos = {50+double(randomTool::genRandomNumBase10(700)),150+double(randomTool::genRandomNumBase10(700))};
               inserted = true;
               for(int j = 0 ; i<positions.size() and inserted;++j){
                   if(positions[j] == new_pos) inserted = false;
               }
        }while (!inserted);
        positions.push_back(new_pos);
    }
    std::vector<long double> temp;
    for(int i = 0; i < nCities;++i){
        temp.clear();
        for(int j = 0;j < nCities;++j){
            temp.push_back(distance2points(positions[i],positions[j]));
        }
        distances.push_back(temp);
    }


}

problem::problem(std::string path,int cities) {
    std::pair<long double,std::vector<position>> instance;
    instance = getInstance(path);
    long double result = instance.first;
    std::vector<long double> temp;
    for(int i = 0; i < cities;++i){
        temp.clear();
        for(int j = 0;j < cities;++j){
            temp.push_back(distance2points(instance.second[i],instance.second[j]));
        }
        distances.push_back(temp);
    }
    optimalLength = result;

}

std::vector<std::vector<long double>> problem::getDistances() {
    return distances;
}

position &problem::operator[](int index) {
    return positions[index];
}

long double problem::getOptimalLen() {
    return optimalLength;
}