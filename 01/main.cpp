
#include <iostream>
#include "utils.h"
#include <string>
#include <cassert>

void Part1() {
    std::string line;
    int num = 50;
    int ans = 0;
    while (std::getline(std::cin, line)) { 
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
    std::cout << ans << std::endl;
}

void Part2() {
    std::string line;
    int num = 50;
    int ans = 0;
    while (std::getline(std::cin, line)) { 
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
    std::cout << ans << std::endl;
}

int main(int argc, char* argv[]) {
    // Part1();
    Part2();
    return 0;
}