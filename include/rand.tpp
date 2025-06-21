#pragma once
#include <random>

template<typename T>
T randomChoice(const T* arr, int size) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, size - 1);
    return arr[dist(gen)];
}
