
#include <iostream>
#include "utils.h"
#include <string>

int main(int argc, char* argv[]) {
    std::string line;
    while (std::getline(std::cin, line)) { 
        auto parts = Split(line, " ");
        for (const auto& part : parts) {
            std::cout << part << std::endl;
        }
        std::cout << "--------------------------------" << std::endl;
    }
    return 0;
}