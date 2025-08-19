#pragma once
#include <random>

class RandomEngine
{
public:
    RandomEngine() : gen(rd()) {}

    int getRandomInt(int minInclusive, int maxInclusive) {
        std::uniform_int_distribution<> dist(minInclusive, maxInclusive);
        return dist(gen);
    }

    short getRandomShort(short minInclusive, short maxInclusive) {
        std::uniform_int_distribution<> dist(minInclusive, maxInclusive);
        return dist(gen);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
};

