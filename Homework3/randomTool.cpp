#include "randomTool.h"

std::mt19937_64 randomTool::g_randomGenerator;

void initRandomClass() {
    std::mt19937_64 initializer;
    initializer.seed(static_cast<unsigned long long int>(std::chrono::high_resolution_clock::now().time_since_epoch().count() ) );
    initializer.discard(10000);
    randomTool::g_randomGenerator.seed(initializer());
}

bool randomTool::genRandomBit() {
    return g_randomGenerator()%2;
}

short randomTool::genRandomNumBase10(int moduloX) {
    return short(abs(short(g_randomGenerator())%moduloX));
}
