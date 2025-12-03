#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.h"

unsigned long long Part1(std::istringstream& input) {
    unsigned long long ans = 0;

    std::string line;
    while (std::getline(input, line)) {
        int largestNum = -1;
        size_t largestNumIndex = 0;
        for (int i = 0; i < line.length()-1; i++) {
            int num = (line[i] - '0');
            if (num > largestNum) {
                largestNum = num;
                largestNumIndex = i;
            }
        }
        int secondLargestNum = -1;
        for (int i = largestNumIndex+1; i < line.length(); i++) {
            int num = (line[i] - '0');
            if (num > secondLargestNum) {
                secondLargestNum = num;
            }
        }
        ans += largestNum * 10 + secondLargestNum;
    }

    return ans;
}

unsigned long long Part2(std::istringstream& input) {
    const int NUM_BATTERIES = 12;
    std::string line;
    unsigned long long ans = 0;
    while (std::getline(input, line)) {
        std::string joltage = "";
        int startIndex = 0;
        for (int numBattersPicked = 0; numBattersPicked < NUM_BATTERIES; numBattersPicked++) {
            int largestNum = -1;
            int index = -1;
            for (int i = startIndex; i < line.length()-NUM_BATTERIES + 1 + numBattersPicked; i++) {
                int num = (line[i] - '0');
                if (num > largestNum) {
                    largestNum = num;
                    index = i;
                }
            }
            startIndex = index + 1;
            joltage += std::to_string(largestNum);
        }

        ans += std::stoull(joltage);
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
