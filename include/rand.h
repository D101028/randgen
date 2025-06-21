#ifndef RAND_H
#define RAND_H 1

#include <string>

template<typename T>
T randomChoice(const T* arr, int size);

#include "rand.tpp"

std::string randomString(const std::string chars, unsigned int length);

std::string getRandomLetters(unsigned int length = 1);

std::string getRandomChars(unsigned int length = 1, bool space_included = false);

extern std::string alphabetsCaptalized;
extern std::string alphabetsLowercase;
extern std::string numbers;
extern std::string symbols;

#endif