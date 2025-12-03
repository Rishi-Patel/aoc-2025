#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.h"

// Start by choosing the most significant digit/battery. 
// We want to pick the largest number/battery possible while leaving enough batteries to the chosen battery's right
// so that we can pick the next numBatteries-1 batteries. We repeat this process for every battery, starting at the 
// battery immediately to the right of the last chosen battery
unsigned long long CalculateMaxJoltage(const std::string& bank, size_t numBatteries) {
    std::string joltage = "";
    int startIndex = 0;
    for (int numBatteriesPicked = 0; numBatteriesPicked < numBatteries; numBatteriesPicked++) {
        int largestNum = -1;
        int index = -1;
        for (int i = startIndex; i < bank.length()-numBatteries + 1 + numBatteriesPicked; i++) {
            int num = (bank[i] - '0');
            if (num > largestNum) {
                largestNum = num;
                index = i;
            }
        }
        startIndex = index + 1;
        joltage += std::to_string(largestNum);
    }
    return std::stoull(joltage);
}

unsigned long long Part1(std::istringstream& input) {
    unsigned long long ans = 0;

    std::string line;
    while (std::getline(input, line)) {
            ans += CalculateMaxJoltage(line, 2);
    }

    return ans;
}

unsigned long long Part2(std::istringstream& input) {
    std::string line;
    unsigned long long ans = 0;
    while (std::getline(input, line)) {
        ans += CalculateMaxJoltage(line, 12);
    }

    return ans;
}

int main(int argc, char* argv[]) {
    auto [part1_input, part2_input] = ReadInput();
    
    auto start1 = std::chrono::high_resolution_clock::now();
    unsigned long long part1_answer = Part1(part1_input);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1\tAnswer: " << part1_answer << "\tTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << " µs" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    unsigned long long part2_answer = Part2(part2_input);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2\tAnswer: " << part2_answer << "\tTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << " µs" << std::endl;
    return 0;
}
