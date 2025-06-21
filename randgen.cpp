#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

#include "rand.h"
#include "uuid.h"

std::string help = R"(Usage: randgen [options...]
Generate a random password/UUID. If no arguments were passed, use the default arguments: 
-ans -l 15 --strict
If at least one of -a, -n, -s was given, then it will only generate from the given types; otherwise, -a, -n, -s will all be seen as given. 

Options:
  -h, --help            Show this message
  -a, --alphabet        Accept English letters (A-Z, a-z)
  -n, --number          Accept numbers 0~9
  -s, --symbol          Accept symbols except space
  --captalized          Only accept captalized letters (A-Z)
  --lowercase           Only accept lowercase letters (a-z)
  -l, --length <length> Output length of the password (default: 15)
  --strict              Ensure the password containing all kinds of characters
  -u, --uuid            Generate a UUID (v4))";

struct Config {
    std::vector<std::string> keys;
    std::vector<std::string> values;
    std::map<std::string, std::string> map;
};

template<typename T>
bool isInVector(T item, std::vector<T> v) {
    for (const auto& j : v) {
        if (item == j) {
            return true;
        }
    }
    return false;
}

Config extractArgs(const std::vector<std::string>& args, const std::vector<std::string>& mapKeys) {
    Config conf;
    std::set<std::string> mapKeySet(mapKeys.begin(), mapKeys.end());
    for (const auto& key : mapKeys) {
        conf.map[key] = "";
    }

    for (size_t i = 0; i < args.size(); ++i) {
        const std::string& item = args[i];
        if (item.rfind("--", 0) == 0) {
            std::string key = item.substr(2);
            if (mapKeySet.count(key) && (i + 1 < args.size()) && args[i + 1][0] != '-') {
                conf.map[key] = args[++i];
            } else {
                conf.keys.push_back(key);
            }
        } else if (item[0] == '-' && item.length() > 1 && item[1] != '-') {
            for (size_t j = 1; j < item.length(); ++j) {
                std::string key(1, item[j]);
                if (mapKeySet.count(key) && i + 1 < args.size() && args[i + 1][0] != '-') {
                    conf.map[key] = args[++i];
                } else {
                    conf.keys.push_back(key);
                }
            }
        } else {
            conf.values.push_back(item);
        }
    }
    return conf;
}

std::string generatePassword(
    bool toShowHelp, 
    bool acceptAlphabet, 
    bool acceptNumber, 
    bool acceptSymbol, 
    bool captalize, 
    bool lowercase, 
    unsigned int length, 
    bool isStrict
) {
    if (toShowHelp) {
        return help;
    }
    std::string chars;
    if (acceptAlphabet) {
        if (captalize) {
            chars += alphabetsCaptalized;
        } else if (lowercase) {
            chars += alphabetsLowercase;
        } else {
            chars += alphabetsCaptalized;
            chars += alphabetsLowercase;
        }
    }
    if (acceptNumber)
        chars += numbers;
    if (acceptSymbol) 
        chars += symbols;
    return randomString(chars, length);
}

int main(int argc, char* argv[]) {
    Config conf = Config();

    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }
    conf = extractArgs(args, {"l", "length"});
    
    bool toShowHelp = false;
    bool acceptAlphabet = false;
    bool acceptNumber = false;
    bool acceptSymbol = false;
    bool captalize = false;
    bool lowercase = false;
    unsigned int length = 15;
    bool isStrict = false;

    // keys
    for (const auto& key : conf.keys) {
        if (key == "h" || key == "help") {
            toShowHelp = true;
        } else if (key == "a" || key == "alphabet") {
            acceptAlphabet = true;
        } else if (key == "n" || key == "number") {
            acceptNumber = true;
        } else if (key == "s" || key == "symbol") {
            acceptSymbol = true;
        } else if (key == "captalized") {
            captalize = true;
        } else if (key == "lowercase") {
            lowercase = true;
        } else if (key == "strict") {
            isStrict = true;
        } else if (key == "u" | key == "uuid") {
            std::cout << generateUUIDv4() << std::endl;
            return 0;
        }
    }

    // values

    // map
    for (const auto& s : conf.map) {
        if (s.second == "") {
            continue;
        }
        if (s.first == "l" || s.first == "length") {
            length = std::stoi(s.second); 
        }
    }

    if (!acceptAlphabet && !acceptNumber && !acceptSymbol) {
        acceptAlphabet = true;
        acceptNumber = true;
        acceptSymbol = true;
    }
    
    auto result = generatePassword(
        toShowHelp, 
        acceptAlphabet, 
        acceptNumber, 
        acceptSymbol, 
        captalize, 
        lowercase, 
        length, 
        isStrict);

    std::cout << result << std::endl;

    return 0; 
}
