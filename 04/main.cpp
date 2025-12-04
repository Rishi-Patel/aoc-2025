#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.h"

// Check the eight adjacent cells, if 4 or more are true, return false, otherwise return true
bool CheckAdjacent(const std::vector<std::vector<bool>>& map, int i, int j) {
    int countAdjacent = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue;
            if (i + di < 0 || i + di >= map.size() || j + dj < 0 || j + dj >= map[i].size()) continue;
            if (map[i + di][j + dj]) countAdjacent++;
        }
    }
    return countAdjacent < 4;
}

unsigned long long Part1(std::istringstream& input) {
    unsigned long long ans = 0;

    std::string line;
    std::vector<std::vector<bool>> map;

    while (std::getline(input, line)) {
        map.push_back(std::vector<bool>());
        for (char c : line) {
            map.back().push_back(c == '@');
        }
    }

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j]) {
                if (CheckAdjacent(map, i, j)) {
                    ans++;
                }
            }
        }
    }

    return ans;
}

unsigned long long Part2(std::istringstream& input) {
    unsigned long long ans = 0;

    std::string line;
    std::vector<std::vector<bool>> map;

    while (std::getline(input, line)) {
        map.push_back(std::vector<bool>());
        for (char c : line) {
            map.back().push_back(c == '@');
        }
    }
    // lazy wrap part 1 code in a while loop. We're done when our ans doesnt change anymore.
    while (true) {
        auto oldAns = ans;
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j]) {
                    if (CheckAdjacent(map, i, j)) {
                        ans++;
                        map[i][j] = false;
                    }
                }
            }
        }
        if (oldAns == ans) {
            break;
        }
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
