#ifndef TSPGA_RANDOMTOOL_H
#define TSPGA_RANDOMTOOL_H

#include <random>
#include <chrono>

class randomTool{
private:
    static std::mt19937_64 g_randomGenerator;
    friend void initRandomClass();
public:
    static short genRandomNumBase10(int moduloX);
    static bool genRandomBit();
};
void initRandomClass();


#endif //TSPGA_RANDOMTOOL_H
