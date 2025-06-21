#include <iostream>
#include <random>
#include <string>

#include "rand.h"

std::string randomString(const std::string chars, unsigned int length) {
    std::string result;
    for (int i = 0; i < length; i++) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, chars.size()-1);
        
        result += chars[dist(gen)];
    }
    return result;
}

std::string getRandomLetters(unsigned int length) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 51);

    std::string result;
    for (unsigned int i = 0; i < length; i++) {
        char ch = dist(gen);
        result += (ch < 26) ? ('A' + ch) : ('a' + ch - 26);
    }
    return result;
}

std::string getRandomChars(unsigned int length, bool space_included) {
    // ASCII 33(32)~126
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(int(!(space_included)), 94);
    
    std::string result;
    for (unsigned int i = 0; i < length; i++) {
        char ch = dist(gen);
        result += ' ' + dist(gen);
    }
    return result;
}

std::string alphabetsCaptalized = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string alphabetsLowercase = "abcdefghijklmnopqrstuvwxyz";
std::string numbers = "0123456789";
std::string symbols = R"(`-=[]\;',./~!@#$%^&*()_+{}|":<>?)";