#include "parser.h"

bool position::operator==(const position &rhs) {
    if(this->x == rhs.x and this->y==rhs.y)return true;
    return false;
}

std::pair<long double, std::vector<position>> getInstance(const std::string& path){
    std::ifstream fin(PATH + path);
    std::vector<position> positions;
    std::pair<long double,std::vector<position>> instance;

    long double element;
    long double past;
    int k=0,i=0,sw;

    while (fin >> element)
    {
        sw=k%2;
        switch(sw){
            case 0:{past=element;}
            case 1:{positions.push_back(position());
                positions[i].x=past;
                positions[i].y=element;
                i++;
            }
        }
        k++;
    }
    for(i=1;i<k;i=i+2){
        instance.second.push_back(positions[i]);
    }

    fin>>element;
    instance.first=element;

    return instance;
}