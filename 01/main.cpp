
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include "utils.h" 

unsigned long long Part1(std::istringstream& input) {
    std::string line;
    int num = 50;
    int ans = 0;
    while (std::getline(input, line)) { 
        if (line[0]  == 'L') {
            num -= std::stoi(line.substr(1));
        }
        else if (line[0] == 'R') {
            num += std::stoi(line.substr(1));
        }
        if (num < 0) {
            num += 100;
        }
        num = num % 100;
        if (num == 0) {
            ans++;
        }
    }
    return ans;
}

unsigned long long Part2(std::istringstream& input) {
    std::string line;
    int num = 50;
    int ans = 0;
    while (std::getline(input, line)) { 
        int old = num;
        if (line[0]  == 'L') {
            num -= std::stoi(line.substr(1));
        }
        else if (line[0] == 'R') {
            num += std::stoi(line.substr(1));
        }
        // Account for case where we land on 0
        if (num == 0) {
            ans++;
        }
        // Account for first left to right or right to left
        if (num * old < 0) {
            ans++;
        }
        // Accoutnf for full rotations
        ans += std::abs(num / 100);

        // Move num back to 0-99
        num = num % 100;
        if (num < 0) {
            num += 100;
        }
    }
    return ans;
}

int main(int argc, char* argv[]) {
    auto [part1_input, part2_input] = ReadInput();
    
    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long part1_answer = Part1(part1_input);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1\tAnswer: " << part1_answer << "\tTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start).count() << " µs" << std::endl;

    unsigned long long part2_answer = Part2(part2_input);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2\tAnswer: " << part2_answer << "\tTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - end1).count() << " µs" << std::endl;
    return 0;
}